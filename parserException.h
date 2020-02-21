class ParserException : public std::exception
{
   int m_Pos;
 
public:
   ParserException(const std::string& message, int pos):
      std::exception(message.c_str()),
      m_Pos(pos)
   {
   }
};
