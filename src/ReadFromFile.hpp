# pragma once
# include "Main.hpp"

class ReadFromFile
{
public:
    ReadFromFile();
    void Reader(String f);
    void setCanpushGadget(bool b)
    {
        m_canpush_gadget = b;
    }
    void setCanpushAnswer(bool b)
    {
        m_canpush_answer = b;
    }
    void setCanpushDisp(bool b)
    {
        m_canpush_disp = b;
    }

    bool getCanpushGadget()
    {
        return m_canpush_gadget;
    }
    bool getCanpushAnswer()
    {
        return m_canpush_answer;
    }
    bool getCanpushDisp()
    {
        return m_canpush_disp;
    }
    
    void setGadget(String l)
    {
        if(l != U"--g--")
        {
            m_gadget.push_back(l);
        }
    }
    void setAnswer(String l)
    {
        if(l != U"--ans--")
        {
            m_answer.push_back(l);
        }
    }
    void setDisp(String l)
    {
        if(l != U"--disp--")
        {
            m_disp.push_back(l);
        }
    }
    void debug(){
        Print << U"gadget";
        for(auto g : m_gadget)
        {
            Print << U"{}"_fmt(g);
        }
        Print << U"ans";

        for(auto a : m_answer)
        {
            Print << U"{}"_fmt(a);
        }
        Print << U"disp";

        for(auto d : m_disp)
        {
            Print << U"{}"_fmt(d);
        }
    }
private:
    String line;
    std::vector<String> m_gadget;
    std::vector<String> m_answer;
    std::vector<String> m_disp;
    bool m_canpush_gadget;
    bool m_canpush_answer;
    bool m_canpush_disp;
};
