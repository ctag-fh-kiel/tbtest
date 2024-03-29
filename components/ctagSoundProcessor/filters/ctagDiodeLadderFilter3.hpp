/***************
CTAG TBD >>to be determined<< is an open source eurorack synthesizer module.

A project conceived within the Creative Technologies Arbeitsgruppe of
Kiel University of Applied Sciences: https://www.creative-technologies.de

(c) 2020 by Robert Manzke. All rights reserved.

The CTAG TBD software is licensed under the GNU General Public License
(GPL 3.0), available here: https://www.gnu.org/licenses/gpl-3.0.txt

The CTAG TBD hardware design is released under the Creative Commons
Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0).
Details here: https://creativecommons.org/licenses/by-nc-sa/4.0/

CTAG TBD is provided "as is" without any express or implied warranties.

License and copyright details for specific submodules are included in their
respective component folders / files if different from this license.
***************/

#pragma once

#include "ctagFilterBase.hpp"

namespace CTAG::SP::HELPERS {
    class ctagDiodeLadderFilter3 : public ctagFilterBase {
    public:
        virtual void SetCutoff(float cutoff) override;

        virtual void SetResonance(float resonance) override;

        virtual void SetSampleRate(float fs) override;

        virtual float Process(float in) override;

        virtual void Init() override;
        void Debug() override;

    private:
        float b_aflt1, b_aflt2, b_aflt3, b_aflt4;
        float b_fres, b_fenv;
        float b_lf, b_lfcut, b_lfgain;
    };

}

