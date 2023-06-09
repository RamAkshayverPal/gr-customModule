/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/customModule/ofdm_equalizer_base.h>

namespace gr {
namespace customModule {

// *** Base class ****************************************************
ofdm_equalizer_base::ofdm_equalizer_base(int fft_len) : d_fft_len(fft_len) {}


ofdm_equalizer_base::~ofdm_equalizer_base() {}


// *** Sub-Base class for 1D equalizers using pilot tones *************
ofdm_equalizer_1d_pilots::ofdm_equalizer_1d_pilots(
    int fft_len,
    const std::vector<std::vector<int>>& occupied_carriers,
    const std::vector<std::vector<int>>& pilot_carriers,
    const std::vector<std::vector<gr_complex>>& pilot_symbols,
    int symbols_skipped,
    bool input_is_shifted)
    : ofdm_equalizer_base(fft_len),
      d_occupied_carriers(fft_len, false),
      d_pilot_carriers(pilot_carriers.size(), std::vector<bool>(fft_len, false)),
      d_pilot_symbols(pilot_symbols.size(),
                      std::vector<gr_complex>(fft_len, gr_complex(0, 0))),
      d_symbols_skipped(symbols_skipped),
      d_pilot_carr_set(pilot_carriers.empty() ? 0
                                              : symbols_skipped % pilot_carriers.size()),
      d_channel_state(fft_len, gr_complex(1, 0))
{
    int fft_shift_width = 0;
    if (input_is_shifted) {
        fft_shift_width = fft_len / 2;
    }
    if (occupied_carriers.empty()) {
        std::fill(d_occupied_carriers.begin(), d_occupied_carriers.end(), true);
    } else {
        for (unsigned i = 0; i < occupied_carriers.size(); i++) {
            for (unsigned k = 0; k < occupied_carriers[i].size(); k++) {
                int carr_index = occupied_carriers[i][k];
                if (occupied_carriers[i][k] < 0) {
                    carr_index += fft_len;
                }
                if (carr_index >= fft_len || carr_index < 0) {
                    throw std::invalid_argument("data carrier index out of bounds.");
                }
                d_occupied_carriers[(carr_index + fft_shift_width) % fft_len] = true;
            }
        }
    }
    if (!pilot_carriers.empty()) {
        for (unsigned i = 0; i < pilot_carriers.size(); i++) {
            if (pilot_carriers[i].size() != pilot_symbols[i].size()) {
                throw std::invalid_argument("pilot carriers and -symbols do not match.");
            }
            for (unsigned k = 0; k < pilot_carriers[i].size(); k++) {
                int carr_index = pilot_carriers[i][k];
                if (pilot_carriers[i][k] < 0) {
                    carr_index += fft_len;
                }
                if (carr_index >= fft_len || carr_index < 0) {
                    throw std::invalid_argument("pilot carrier index out of bounds.");
                }
                d_pilot_carriers[i][(carr_index + fft_shift_width) % fft_len] = true;
                d_pilot_symbols[i][(carr_index + fft_shift_width) % fft_len] =
                    pilot_symbols[i][k];
            }
        }
    }
}


ofdm_equalizer_1d_pilots::~ofdm_equalizer_1d_pilots() {}


void ofdm_equalizer_1d_pilots::reset()
{
    std::fill(d_channel_state.begin(), d_channel_state.end(), gr_complex(1, 0));
    d_pilot_carr_set =
        d_pilot_carriers.empty() ? 0 : d_symbols_skipped % d_pilot_carriers.size();
}


void ofdm_equalizer_1d_pilots::get_channel_state(std::vector<gr_complex>& taps)
{
    taps = d_channel_state;
}

} /* namespace customModule */
} /* namespace gr */
