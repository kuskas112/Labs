#include "SECD.hpp"

void drop_error()
{
    std::cerr << "Analyze error!!!\n";
    std::exit(EXIT_FAILURE);
}

void drop_error(std::string str)
{
    std::cerr << str << "\n";
    std::exit(EXIT_FAILURE);
}


class SECD
{
    private:

    pStack_Type stack;
    pEnviroment_Type env;
    pControl_list_Type com;
    pDump_Type dump;


    public:

    SECD()
    {
        this->stack = std::make_shared<Stack_Type>();
        this->env = nullptr;
        this->com = std::make_shared<Control_list_Type>();
        this->dump = std::make_shared<Dump_Type>();

        this->push_command(STOP, "STOP");
    }

    void get_program(pnode node, std::shared_ptr<Enviroment> env = nullptr, bool is_quoted = false)
    {
        if (!node) return;
        switch (node->token)
        {
            /* BAZED */
            case S_ATOM:

                break;
            case D_ATOM:
                push_command<int>(LDC, "LDC", node->label.num);
                break;
            
            /* MATH */

            case ADD:
                push_command(ADD, "ADD");
                break;
            case SUB:
                push_command(SUB, "SUB");
                break;
            case MUL:
                push_command(MUL, "MUL");
                break;
            case DIVE:
                push_command(DIVE, "DIVE");
                break;
            case REM:
                push_command(REM, "REM");
                break;

            /* LOGIC */

            case ATOM_PREDICATE:
                push_command(ATOM_PREDICATE, "ATOM");
                break;
            case EQUAL:
                push_command(EQUAL, "EQUAL");
                break;
            case LE:
                push_command(LE, "LE");
                break;
            case COND:

                break;

            /* LIST */

            case CAR:
                push_command(CAR, "CAR");
                break;
            case CDR:
                push_command(CDR, "CDR");
                break;
            case CONS:
                push_command(CONS, "CONS");
                break;
            case QUOTE:
                push_command(QUOTE, "QUOTE");
                is_quoted = true;
                break;
            default:

                drop_error();
                break;
            
        }

        for (int i = 0; node->children[i] != nullptr; i++)
        {
            get_program(node->children[i], env, is_quoted);
        }
    }

    void push_command(int tok, std::string name = "")
    {
        this->com->push_back(Command(tok, name));
    }

    template <typename... T>
    void push_command(int tok, std::string name = "", T... args)
    {
        Command com(tok, name);
        (com.args.push_back(args), ...);
        this->com->push_back(com);
    }




    void print_commands()
    {
        for (auto it = com->rbegin(); it != com->rend(); it++)
        {
            it->print();
        }
    }

};

class SECD_VM
{



    public:

    
    
};



int main()
{

    get_AST_root();
    print_tree(root, 0);
    puts("END PRINT\n");

    SECD secd = SECD();

    secd.get_program(root, nullptr, false);
    secd.print_commands();



    return 0;
}