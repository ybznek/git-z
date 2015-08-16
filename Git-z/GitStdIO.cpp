#include "GitStdIO.hpp"


gitz::GitStdIO::GitStdIO() : input{}, inStream{&input} {
    input.open(stdin, QFile::ReadOnly);
    output.open(stdout, QFile::WriteOnly);
}

gitz::GitStdIO &gitz::GitStdIO::operator<<(char chr) {
    output.write(&chr, 1);
    return *this;
}

bool gitz::GitStdIO::operator>>(QString &str) {
    str = inStream.readLine();
    return !inStream.atEnd();
}

gitz::GitStdIO &gitz::GitStdIO::operator<<(const QString &str) {
    output.write(str.toLocal8Bit());
    return *this;
}
