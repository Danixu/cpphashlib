/*******************************************************************************
 * 
 * Created by Daniel Carrasco at https://www.electrosoftcloud.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#define DATA_ORDER_IS_LITTLE_ENDIAN

#include <stdint.h>
#include <cstring>
#include <string>
#include <stdio.h>
#include "base.hpp"

#include <stdio.h>



namespace cpphashlib {
    class md5: base {
        public:
            md5();
            md5(const std::string &text);
            md5(char *Input, long length);

            void update(const unsigned char *buf, uint32_t length);
            void update(const char *buf, uint32_t length);
            void finalize();
            std::string hexdigest() const;

        private:
            const int transforms[16] = {
                 7, 12, 17, 22,
                 5,  9, 14, 20,
                 4, 11, 16, 23,
                 6, 10, 15, 21
            };
            void init();
            static const uint8_t blocksize = 64;

            void transform(const uint8_t block[blocksize]);
            static void decode(uint32_t output[], const uint8_t input[], uint32_t len);
            static void encode(uint8_t output[], const uint32_t input[], uint32_t len);
            
            bool finalized;
            uint8_t buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
            uint32_t count[2];   // 64bit counter for number of bits (lo, hi)
            uint32_t state[4];   // digest so far
            uint8_t digest[16]; // the result

    };
}