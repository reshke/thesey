

class ReadAheadBuf {
protected:
    int fd;
public:
    /* accepted client fd */
    ReadAheadBuf(int fd);
};