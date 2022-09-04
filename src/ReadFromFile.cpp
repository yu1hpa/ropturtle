# include "ReadFromFile.hpp"
/*
 *Reader(ここ) -> Parser -> RopElementに格納 -> 描画
 */
ReadFromFile::ReadFromFile()
    : m_canpush_gadget(false)
    , m_canpush_answer(false)
    , m_canpush_disp(false)
{}

void ReadFromFile::Reader(String f)
{
    TextReader reader{ f };
    if (not reader)
    {
        throw Error{ U"Failed to open" };
    }
    String line;
    while (reader.readLine(line))
    {
        if(U"--g--" == line)
        {
            setCanpushGadget(true);
            setCanpushAnswer(false);
            setCanpushDisp(false);
            
        }

        if(U"--ans--" == line)
        {
            setCanpushAnswer(true);
            setCanpushGadget(false);
            setCanpushDisp(false);
        }
        
        if(U"--disp--" == line)
        {
            setCanpushAnswer(false);
            setCanpushGadget(false);
            setCanpushDisp(true);
        }

        if(getCanpushGadget())
        {
            setGadget(line);
        }
        
        if(getCanpushAnswer())
        {
            setAnswer(line);
        }

        if(getCanpushDisp())
        {
            setDisp(line);
        }
    }
}
