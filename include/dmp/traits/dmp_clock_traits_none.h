/*
 * Diff Match and Patch
 * Copyright 2020 The diff-match-patch Authors.
 * https://github.com/google/diff-match-patch
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/*
 * Functions for diff, match and patch.
 * Computes the difference between two texts to create a patch.
 * Applies the patch onto another text, allowing for errors.
 *
 * @author fraser@google.com (Neil Fraser)
 *
 * STL-only port by snhere@gmail.com (Sergey Nozhenko)
 * and some tweaks for std::string by leutloff@sundancer.oche.de (Christian Leutloff)
 * rebased on the current C# version and added constexpr-ness by guntersp0@gmail.com (Gunter Spöcker):
 *
 * Here is a trivial sample program:

#include "diff_match_patch.h"
#include <string>
using namespace std;
int main(int argc, char **argv) {
    diff_match_patch<all_traits<std_wstring_traits, chrono_clock_traits, std_container_traits>> dmp;

    wstring str1 = L"First string in diff";
    wstring str2 = L"Second string in diff";

    wstring strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));
    auto    out(dmp.patch_apply(dmp.patch_fromText(strPatch), str1));
    wstring strResult(out.text2);

    // here, strResult will equal str2 above.
    std::wcout << strResult << "\n";
    return 0;
}
*/


#ifndef DIFF_MATCH_PATCH_CLOCKTRAITS_NONE_H
#define DIFF_MATCH_PATCH_CLOCKTRAITS_NONE_H


#include "dmp/utils/dmp_traits.h"

#include <limits>

namespace dmp {
namespace traits {

template <>
struct clock_traits<void> {
    struct null_clock {
        using type = int64_t;

        static constexpr type null_value = std::numeric_limits<type>::lowest();

        type time = null_value;

        constexpr null_clock() noexcept = default;

        inline constexpr null_clock(type _time) noexcept
            : time(_time) {}

        inline static constexpr null_clock now() noexcept { return { 0 }; }

        inline constexpr null_clock& addMilliseconds(type milliseconds) noexcept {
            time += milliseconds;
            return *this;
        }

        inline constexpr bool operator>(const null_clock& o) const noexcept { return time > o.time; }

        inline constexpr bool hitDeadline() const noexcept {
            if (time == null_value) {
                return false;
            }
            return now().time > time;
        }
    };

    using type = null_clock;
};

}  // namespace traits

using null_clock_traits = traits::clock_traits<void>;

}  // namespace dmp

#endif
