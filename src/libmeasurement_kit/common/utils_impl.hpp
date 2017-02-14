// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef SRC_LIBMEASUREMENT_KIT_COMMON_UTILS_IMPL_HPP
#define SRC_LIBMEASUREMENT_KIT_COMMON_UTILS_IMPL_HPP

#include "../common/utils.hpp"
#include <cstdio>
#include <measurement_kit/common.hpp>

namespace mk {

/*
 * There are many ways in C++ to slurp the whole content of a file into a
 * C++ string. The following is my favourite. Compared to other methods,
 * not only this seems fastest, but also it provides greater control over
 * errors that can occur. Thus mocking is simpler.
 *
 * See <http://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c>.
 */
template <typename T, MK_MOCK_NAMESPACE(std, fopen),
          MK_MOCK_NAMESPACE_SUFFIX(std, fseek, 1),
          MK_MOCK_NAMESPACE(std, ftell),
          MK_MOCK_NAMESPACE_SUFFIX(std, fseek, 2),
          MK_MOCK_NAMESPACE(std, fread), MK_MOCK_NAMESPACE(std, fclose)>
ErrorOr<std::vector<T>> slurpv_impl(std::string p) {
    FILE *filep = fopen(p.c_str(), "rb");
    if (filep == nullptr) {
        return FileIoError();
    }
    if (fseek_1(filep, 0, SEEK_END) != 0) {
        fclose(filep);
        return FileIoError();
    }
    // Note: ftello() might be better for reading very large files but
    // honestly I do think we should use some kind of mmap for them.
    long pos = ftell(filep);
    if (pos < 0) {
        fclose(filep);
        return FileIoError();
    }
    std::vector<T> result;
    // Note: cast to unsigned safe because we excluded negative case above
    result.resize((unsigned long)pos, 0);
    if (fseek_2(filep, 0, SEEK_SET) != 0) {
        fclose(filep);
        return FileIoError();
    }
    size_t nread = fread(result.data(), 1, result.size(), filep);
    // Note: cast to unsigned safe because we excluded negative case above
    if ((unsigned long)pos != nread) {
        fclose(filep);
        return FileIoError();
    }
    // Note: afaik fclose() should not fail when we're just reading
    if (fclose(filep) != 0) {
        return FileIoError();
    }
    return result;
}

} // namespace mk
#endif
