#include "ctagSoundProcessorClaude.hpp"
#include "esp_heap_caps.h"
#include <algorithm>

using namespace CTAG::SP;
using namespace std;

void ctagSoundProcessorClaude::Process(const ProcessData &data) {
    // prepare input buffer
    clouds::ShortFrame in[32];
    for(int i=0;i<bufSz;i++){
        in[i].l = data.buf[i*2] * 32767.f;
        in[i].r = data.buf[i*2 + 1] * 32767.f;
    }

    // setup processor
    clouds::PlaybackMode playbackMode = static_cast<clouds::PlaybackMode>(mode.load());
    processor.set_playback_mode(playbackMode);
    processor.set_quality(quality);
    bool bReverse = reverse;
    if(trig_reverse != -1){
        bReverse = data.trig[trig_reverse] == 1 ? false : true;
    }
    processor.set_reverse(bReverse);
    processor.Prepare();

    // Trigger evaluation
    bool bTrigger = trigger;
    if(trig_trigger != -1){
        bTrigger = data.trig[trig_trigger] == 1 ? false : true;
    }
    if(bTrigger && !preTrigger){
        preTrigger = bTrigger;
        isTriggered = true;
    }else if(!bTrigger && preTrigger){
        preTrigger = bTrigger;
    }else if(bTrigger && preTrigger){
        isTriggered = false;
    }

    clouds::Parameters* p = processor.mutable_parameters();
    p->trigger = isTriggered;
    p->gate = isTriggered;
    bool bFreeze = freeze;
    if(trig_freeze != -1){
        bFreeze = data.trig[trig_freeze] == 1 ? 0 : 1;
    }
    p->freeze = bFreeze;
    float fPosition = position / 4095.f;
    if(cv_position != -1){
        fPosition = fabsf(data.cv[cv_position]);
    }
    p->position = fPosition;
    float fSize = size / 4095.f;
    if(cv_size != -1){
        fSize = fabsf(data.cv[cv_size]);
    }
    if(playbackMode==clouds::PLAYBACK_MODE_STRETCH) fSize *= 0.5f;
    p->size = fSize;
    float fPitch = pitch;
    if(cv_pitch != -1){
        fPitch += 12.f * data.cv[cv_pitch] * 5.f;
    }
    clamp(fPitch, -48.f, 48.f);
    p->pitch = fPitch;
    float fDensity = density / 4095.f;
    if(cv_density != -1){
        fDensity = fabsf(data.cv[cv_density]);
    }
    p->density = fDensity;
    float fTexture = texture / 4095.f;
    if(cv_texture != -1){
        fTexture = fabsf(data.cv[cv_texture]);
    }
    p->texture = fTexture;
    float fDryWet = drywet / 4095.f;
    if(cv_drywet != -1){
        fDryWet = fabsf(data.cv[cv_drywet]);
    }
    p->dry_wet = fDryWet;
    float fWidth = width / 4095.f;
    if(cv_width != -1){
        fWidth = fabsf(data.cv[cv_width]);
    }
    p->stereo_spread = fWidth;
    float fFeedback = feedback / 4095.f;
    if(cv_feedback != -1){
        fFeedback = fabsf(data.cv[cv_feedback]);
    }
    p->feedback = fFeedback;
    float fReverb = reverb / 4095.f;
    if(cv_reverb != -1){
        fReverb = fabsf(data.cv[cv_reverb]);
    }
    p->reverb = fReverb;

    clouds::ShortFrame out[32];
    processor.Process(in, out, 32);

    // back convert buffers from int to float
    for(int i=0;i<bufSz;i++){
        data.buf[i*2] = out[i].l * 0.000030518509476f;
        data.buf[i*2 + 1] = out[i].r * 0.000030518509476f;
    }
}

ctagSoundProcessorClaude::ctagSoundProcessorClaude() {
    // construct internal data model
    knowYourself();
    model = std::make_unique<ctagSPDataModel>(id, isStereo);
    LoadPreset(0);

    // memallocs
    block_mem = (uint8_t *) heap_caps_malloc(memLen, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if(block_mem == NULL){
        ESP_LOGE("Claude", "Cannot alloc DRAM mem trying SPIRAM!");
        block_mem = (uint8_t*) heap_caps_malloc(memLen, MALLOC_CAP_SPIRAM);
        if(block_mem == NULL) {
            ESP_LOGE("Claude", "Cannot alloc mem on SPIRAM!");
            return;
        }
    }
    memset(block_mem, 0, memLen);
    block_ccm = (uint8_t*) heap_caps_malloc(ccmLen, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if(block_ccm == NULL){
        ESP_LOGE("Claude", "Cannot alloc DRAM mem trying SPIRAM!");
        block_ccm = (uint8_t*) heap_caps_malloc(ccmLen, MALLOC_CAP_SPIRAM);
        if(block_ccm == NULL) {
            ESP_LOGE("Claude", "Cannot alloc mem on SPIRAM!");
            return;
        }
    }
    memset(block_ccm, 0, ccmLen);

    processor.Init(block_mem, memLen, block_ccm, ccmLen);
}

ctagSoundProcessorClaude::~ctagSoundProcessorClaude() {
    heap_caps_free(block_mem);
    heap_caps_free(block_ccm);
}

void ctagSoundProcessorClaude::knowYourself(){
    // autogenerated code here
    // sectionCpp0
	pMapPar.emplace("trigger", [&](const int val){ trigger = val;});
	pMapTrig.emplace("trigger", [&](const int val){ trig_trigger = val;});
	pMapPar.emplace("freeze", [&](const int val){ freeze = val;});
	pMapTrig.emplace("freeze", [&](const int val){ trig_freeze = val;});
	pMapPar.emplace("reverse", [&](const int val){ reverse = val;});
	pMapTrig.emplace("reverse", [&](const int val){ trig_reverse = val;});
	pMapPar.emplace("mode", [&](const int val){ mode = val;});
	pMapCv.emplace("mode", [&](const int val){ cv_mode = val;});
	pMapPar.emplace("quality", [&](const int val){ quality = val;});
	pMapCv.emplace("quality", [&](const int val){ cv_quality = val;});
	pMapPar.emplace("position", [&](const int val){ position = val;});
	pMapCv.emplace("position", [&](const int val){ cv_position = val;});
	pMapPar.emplace("size", [&](const int val){ size = val;});
	pMapCv.emplace("size", [&](const int val){ cv_size = val;});
	pMapPar.emplace("pitch", [&](const int val){ pitch = val;});
	pMapCv.emplace("pitch", [&](const int val){ cv_pitch = val;});
	pMapPar.emplace("density", [&](const int val){ density = val;});
	pMapCv.emplace("density", [&](const int val){ cv_density = val;});
	pMapPar.emplace("texture", [&](const int val){ texture = val;});
	pMapCv.emplace("texture", [&](const int val){ cv_texture = val;});
	pMapPar.emplace("feedback", [&](const int val){ feedback = val;});
	pMapCv.emplace("feedback", [&](const int val){ cv_feedback = val;});
	pMapPar.emplace("width", [&](const int val){ width = val;});
	pMapCv.emplace("width", [&](const int val){ cv_width = val;});
	pMapPar.emplace("reverb", [&](const int val){ reverb = val;});
	pMapCv.emplace("reverb", [&](const int val){ cv_reverb = val;});
	pMapPar.emplace("drywet", [&](const int val){ drywet = val;});
	pMapCv.emplace("drywet", [&](const int val){ cv_drywet = val;});
	isStereo = true;
	id = "Claude";
	// sectionCpp0
}