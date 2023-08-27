class ArgParser{
public:
    ArgParser(int ReqQuantity, int HelpArgPos, int argc, char* argv);
    template <typename Type> 
    Type GetArgument(int ArgCtr);
private:
    int HelpArg = 1;
};