template< class T >
class CircularBuffer{
    public:
        CircularBuffer(int FIFOsize)
        {
            m_FIFO = new T[FIFOsize];
            m_size = FIFOsize;
            m_elementcount = 0;
            m_outindex = 0;
        };
        ~CircularBuffer()
        {
            delete[] m_FIFO;          
        };
        T Get()
        {
            m_elementcount--;
            return m_FIFO[(m_outindex++)%m_size];
        };
        void Put(T n)
        {
            m_elementcount++;
            m_FIFO[(m_elementcount+m_outindex)%m_size] = n;
        };
        long GetElementCount()
        {
            return m_elementcount;
        };
    private:
        long    m_size;
        long    m_elementcount;
        long    m_outindex;
        T*      m_FIFO;
    };