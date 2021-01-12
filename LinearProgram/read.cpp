#include"read.hpp"

void Read::read(void) /* main function for reading mps file */
{
    auto begin = chrono::steady_clock::now();
    boost::iostreams::mapped_file mmap(aFileName, boost::iostreams::mapped_file::readonly);
    auto f = mmap.const_data();
    auto l = f + mmap.size();

    uintmax_t m_numLines = 0;
    while (f && f != l) {
        if ((f = static_cast<const char*>(memchr(f, '\n', l - f)))) {
            m_numLines++, f++;
            cout << f << endl;
        }
    }

    cout << "m_numLines = " << m_numLines << "\n";
}