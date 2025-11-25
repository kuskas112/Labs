#include "analyzer.hpp"

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



class Analyzer
{
    private:

    static bool is_empty(Answer* a)
    {
        if (a == nullptr) return true;
        return false;
    }

    static bool is_empty_list(Answer* a)
    {
        if (a->is_list() && a->get_list()->size() == 0) return true;
        return false;
    }

    static bool is_atom(Answer* a)
    {
        if (!a->is_list())
        {
            return true;
        }
        else 
        {
            return is_empty_list(a);
        }
    }

    // static Answer* apply_lambda(pnode lambda_node) // param1: lambda, param2: args
    // {
    //     std::string lambda_name = std::string(lambda_node->children[0]->label.str);
    // }

    public:

    static Answer* exec_command(pnode node, std::shared_ptr<Enviroment> env, bool is_quoted = false)
    {
        if (!node) return nullptr;
        if (!env) drop_error();
        Answer* res = new Answer();

        Answer *a, *b, *c;
        
        //print_node(node);
        switch (node->token)
        {
        /* BAZED */
        case S_ATOM:
            if (is_quoted)
            {
                res->set(std::string(node->label.str));
            }
            else
            {
                auto val = env->get_bind(std::string(node->label.str));
                if (!val) drop_error("Variable " + std::string(node->label.str) + " not found");
                res->set(val->get());
            }

            break;
        case D_ATOM:
            res->set(node->label.num);
            break;
        
        /* MATH */

        case ADD:
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env); 
            if (!a || !b) drop_error();
            if (!a->is_num() && !b->is_num()) drop_error();

            res->set(a->get_int() + b->get_int());
            break;
        case SUB:
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env); 
            if (!a || !b) drop_error();
            if (!a->is_num() && !b->is_num()) drop_error();

            res->set(a->get_int() - b->get_int());
            break;
        case MUL:
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env); 
            if (!a || !b) drop_error();
            if (!a->is_num() && !b->is_num()) drop_error();

            res->set(a->get_int() * b->get_int());
            break;
        case DIVE:
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env); 
            if (!a || !b) drop_error();
            if (!a->is_num() && !b->is_num()) drop_error();

            res->set(a->get_int() / b->get_int());
            break;
        case REM:
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env); 
            if (!a || !b) drop_error();
            if (!a->is_num() && !b->is_num()) drop_error();

            res->set(a->get_int() % b->get_int());
            break;

        /* LIST */

        case CAR:
            a = exec_command(node->children[0], env);
            if (!a) drop_error();
            //if (!a->is_list()) drop_error();

            res->set(a->get_list_head()->get());
            break;
        case CDR:
            a = exec_command(node->children[0], env);
            if (!a) drop_error();
            if (!a->is_list()) drop_error();

            res->set(a->get_list_tail());
            break;
        case CONS:
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env);
            if (!a || !b) drop_error();

            if (!b->is_list()) drop_error();

            a->splice_lists(b);
            res->set(a->get());
            break;
        case QUOTE:
            a = exec_command(node->children[0], env, true);
            res->set(a->get());
            break;
        case LIST: {

            if (is_quoted) // just a list
            {

                pList list = std::make_shared<List>();
                
                for (int i = 0; i < node->num_children; i++)
                {
                    a = exec_command(node->children[i], env, is_quoted);
                    
                    if (!a) drop_error();
                    
                    list->push_back(*a);
                }
                
                res->set(list);
            }
            else // call lambda function
            {
                auto lambda_name = std::string(exec_command(node->children[0], env, true)->get_string());
                
                auto lambda_stuff = env->get_bind(lambda_name);
                if (!lambda_stuff) drop_error("Lambda " + lambda_name + " not found");
                if (!lambda_stuff->is_lambda()) drop_error("String " + lambda_name + " is not a lambda");

                auto lambda = lambda_stuff->get_lambda();
                if (!lambda) drop_error("Lambda " + lambda_name + " is null");
                
                
                if (lambda->get_params_count() != node->num_children-1) drop_error("Lambda " + lambda_name + " has wrong amount of parameters");

                int i = 1;
                for (auto it = lambda->get_params().begin(); it != lambda->get_params().end(); it++)
                {
                    if (!node->children[i]) drop_error("Lambda " + lambda_name + " has wrong amount of parameters");
                    a = exec_command(node->children[i], env);

                    if (!a) drop_error();

                    auto lambda_env = lambda->get_env();

                    if (!lambda_env) drop_error();

                    lambda_env->bind(*it, a->get());

                    i++;
                }

                b = exec_command(lambda->get_body(), lambda->get_env());

                if (!b) drop_error();

                res->set(b->get());
                
            }
        }  break;

        /* BOOL */

        case ATOM_PREDICATE:
            a = exec_command(node->children[0], env);
            if (!a) drop_error();
            res->set(is_atom(a));
            break;
        case EQUAL: // добавить сравнения списков 
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env);
            if (!a || !b) drop_error();
            if (!(is_atom(a) || is_atom(b))) throw std::runtime_error("One of el must be atom");

            if (a->is_num() && b->is_num()) 
            {
                res->set(a->get_int() == b->get_int());
            }
            else if (is_empty_list(a) && is_empty_list(b))
            {
                res->set(true);
            }
            else {
                res->set(false);
            }
            
            break;
        case LE:
            a = exec_command(node->children[0], env); b = exec_command(node->children[1], env);
            if (!a || !b) drop_error();
            if (!a->is_num() && !b->is_num()) drop_error();

            res->set(a->get_int() <= b->get_int());
            break;
        case COND:
            a = exec_command(node->children[0], env);

            if (is_empty(a)) drop_error();

            if (a->get_int())
            {
                b = exec_command(node->children[1], env);
            }
            else
            {
                b = exec_command(node->children[2], env);
            }

            if (!b) drop_error();
            res->set(b->get());
            break;

        /* LAMBDA */

        case LAMBDA: {

            if (node->num_children != 2) drop_error();
                
            pnode params_node = node->children[0];
            pnode body_node = node->children[1];

            //Lambda lambda = Lambda(body_node, env);
            std::shared_ptr<Lambda> lambda = std::make_shared<Lambda>(body_node, env);

            if (params_node->token != PARAM_LIST) drop_error();

            //pList list = std::make_shared<List>();

            for (int i = 0; i < params_node->num_children; i++)
            {
                lambda->add_param(std::string(params_node->children[i]->label.str));
            }

            res->set(lambda);

            } break;
        case LETREC:
        case LET: {
            auto lambda = std::make_shared<Lambda>(node->children[0], env);

            exec_command(node->children[1], lambda->get_env()); // PAIR_LIST

            a = exec_command(node->children[0], lambda->get_env());
            if (!a) drop_error();
            res->set(a->get());
            
        } break;
        

        /* TEMP */

        case PAIR_LIST: {

            for (int i = 0; i < node->num_children; i++)
            {
                exec_command(node->children[i], env);
            }
        } break;

        case PAIR:
            a = exec_command(node->children[0], env, true); b = exec_command(node->children[1], env);
            if (!a || !b) drop_error();

            env->add_binding(a->get_string(), b->get());

            break;

        
        default:
            std::cerr << "Syntax Error: Unknown command \ntoken:" << node->token << "\n";
            break;
        }

        return res;
    }

    static void print_answer(Answer* ans, bool is_list = false)
    {
        if (!ans) drop_error();
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
            {
                //std::cout << "Answer (num): ";
                std::cout << arg;
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                //std::cout << "Answer (string): ";
                std::cout << arg;
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<List>>)
            {
                //std::cout << "Answer (list): ";
                std::cout << "[";
                bool first = true;
                for (auto& i : *arg)
                {
                    if (!first) std::cout << ", ";
                    print_answer(&i);
                    first = false;
                }
                std::cout << "]";
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<Lambda>>)
            {
                //std::cout << "Answer (lambda): ";
                arg->print();
            }
        }, ans->get());

        //std::cout << "\n";
    }


};

int main() {

    get_AST_root();
    print_tree(root, 0);
    puts("END PRINT\n");

    auto global_env = std::make_shared<Enviroment>();
    //global_env->add_binding("a", 10);

    Answer* answer = Analyzer::exec_command(root, global_env);
    Analyzer::print_answer(answer);
    std::cout << "\n";
    
    return 0;
}