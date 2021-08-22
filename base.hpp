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

namespace cpphashlib {
    class base {
        protected:
            static inline uint32_t rotate_left(uint32_t x, int n){
                return (x << n) | (x >> (32-n));
            }
            static inline uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
                return x&y | ~x&z;
            }
            static inline uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
                return x&z | y&~z;
            }
            static inline uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
                return x^y^z;
            }
            static inline uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
                return y ^ (x | ~z);
            }
            static inline void FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
                a = rotate_left(a+ F(b,c,d) + x + ac, s) + b;
            };
            static inline void GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
                a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
            }
            static inline void HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
                a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
            }
            static inline void II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
                a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
            }
    };
}