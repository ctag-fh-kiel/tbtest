#include <atomic>
#include <vector>
#include "ctagSoundProcessor.hpp"

#include "helpers/ctagWNoiseGen.hpp"
#include "helpers/ctagSineSource.hpp"
#include "helpers/ctagDecay.hpp"
#include "helpers/ctagADEnv.hpp"
#include "braids/analog_oscillator.h"
#include "stmlib/dsp/filter.h"
#include "mifx/pitch_shifter.h"


namespace CTAG {
    namespace SP {
        class ctagSoundProcessorAntique : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;
            ctagSoundProcessorAntique();
            virtual ~ctagSoundProcessorAntique();

        private:
            virtual void knowYourself() override;

            HELPERS::ctagWNoiseGen rnd, hissLevelMod;
            HELPERS::ctagWNoiseGen pop1, pop2, click;
            HELPERS::ctagSineSource popSrc;
            HELPERS::ctagDecay popShaper;
            stmlib::Svf clickFilter;
            stmlib::Svf hissFlt, scrubFilt;
            braids::AnalogOscillator humm;
            mifx::PitchShifter fx;
            float *fx_buffer;
            HELPERS::ctagSineSource lfoWow, lfoFlutter, lfoPopBlend;
            stmlib::Svf lpMaster, hpMaster;

            uint32_t loopCntr;
            int32_t seed1, seed2;

            // private attributes could go here
            // autogenerated code here
            // sectionHpp
	atomic<int32_t> inplevel, cv_inplevel;
	atomic<int32_t> inpdist, cv_inpdist;
	atomic<int32_t> inprepitch, cv_inprepitch;
	atomic<int32_t> hisslevel, cv_hisslevel;
	atomic<int32_t> hissf, cv_hissf;
	atomic<int32_t> hissbw, cv_hissbw;
	atomic<int32_t> hissshp, cv_hissshp;
	atomic<int32_t> scrublev, cv_scrublev;
	atomic<int32_t> scrubcen, cv_scrubcen;
	atomic<int32_t> scrubq, cv_scrubq;
	atomic<int32_t> scrubmodlev, cv_scrubmodlev;
	atomic<int32_t> humlev, cv_humlev;
	atomic<int32_t> humf, cv_humf;
	atomic<int32_t> humshape, cv_humshape;
	atomic<int32_t> humagr, cv_humagr;
	atomic<int32_t> wowl, cv_wowl;
	atomic<int32_t> wowf, cv_wowf;
	atomic<int32_t> flutl, cv_flutl;
	atomic<int32_t> flutf, cv_flutf;
	atomic<int32_t> clickl, cv_clickl;
	atomic<int32_t> clickd, cv_clickd;
	atomic<int32_t> clickf, cv_clickf;
	atomic<int32_t> clickfmod, cv_clickfmod;
	atomic<int32_t> clickq, cv_clickq;
	atomic<int32_t> clickqm, cv_clickqm;
	atomic<int32_t> popl, cv_popl;
	atomic<int32_t> popd1, cv_popd1;
	atomic<int32_t> popd2, cv_popd2;
	atomic<int32_t> poplen, cv_poplen;
	atomic<int32_t> poplensy, trig_poplensy;
	atomic<int32_t> popblen, cv_popblen;
	atomic<int32_t> popf, cv_popf;
	atomic<int32_t> popdcy, cv_popdcy;
	atomic<int32_t> outlevel, cv_outlevel;
	atomic<int32_t> outfltctr, cv_outfltctr;
	atomic<int32_t> outfltbw, cv_outfltbw;
	atomic<int32_t> outfltq, cv_outfltq;
	atomic<int32_t> hishumpre, trig_hishumpre;
	// sectionHpp
        };
    }
}