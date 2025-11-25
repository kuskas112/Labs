#pragma once


extern "C" {
    #include "tree.h"
    #include "y.tab.h"

    extern pnode root;
    extern pnode get_AST_root();
}

#include <iostream>
#include <variant>
#include <cstring>
#include <string>
#include <unordered_map>
#include <list>
#include <memory>
#include <cstdlib>

#include <functional>

#include <map>

//typedef std::variant<int, std::string, std::list<int>>


class Answer;
class Lambda;
class Enviroment;

using List = std::list<Answer>;

//typedef std::variant<int, std::string,std::shared_ptr<List>> Answer_Value;
using Answer_Value = std::variant<int, std::string, std::shared_ptr<List>, std::shared_ptr<Lambda>>;
using pList = std::shared_ptr<List>;

class Answer
{
    private:

    Answer_Value value;

    public:

    Answer()
    {
        this->value = {0};
    }

    Answer(Answer_Value value)
    {
        this->value = std::move(value);
    }

    void set(Answer_Value value)
    {
        this->value = std::move(value);
    }

    Answer_Value get()
    {
        return this->value;
    }

    std::string get_string()
    {
        if (!this->is_str()) throw std::runtime_error("not a string");
        return std::get<std::string>(this->value);
    }
    
    int get_int()
    {
        if (!this->is_num()) throw std::runtime_error("not a number");
        return std::get<int>(this->value);
    }

    std::shared_ptr<Lambda> get_lambda()
    {
        if (!this->is_lambda()) throw std::runtime_error("not a lambda");
        return std::get<std::shared_ptr<Lambda>>(this->value);
    }

    std::shared_ptr<List> get_list()
    {
        if (!this->is_list()) throw std::runtime_error("not a list");
        return std::get<std::shared_ptr<List>>(this->value);
    }

    bool is_num()
    {
        return value.index() == 0;
    }

    bool is_str()
    {
        return value.index() == 1;
    }

    bool is_list()
    {
        return value.index() == 2;
    }

    bool is_lambda()
    {
        return value.index() == 3;
    }

    Answer* get_list_head()
    {
        //std::get<std::shared_ptr<List>>(a->get())->front()
        Answer* head = new Answer();
        head = &std::get<std::shared_ptr<List>>(this->value)->front();
        return head;
    }

    pList get_list_tail()
    {
        pList tail = std::get<std::shared_ptr<List>>(this->value);
        tail->pop_front();
        return tail;
    }

    // void merge_lists(pList l)
    // {
    //     //std::get<std::shared_ptr<List>>(this->value)->merge(*l);
    //     return;
    // }

    void merge_lists(Answer* l)
    {
        auto curr = std::get<std::shared_ptr<List>>(this->value);
        auto other = std::get<std::shared_ptr<List>>(l->get());
        curr->splice(curr->end(), *other);
        return;
    }

    void splice_lists(Answer* l)
    {
        try 
        { 
            auto list = std::get<std::shared_ptr<List>>(l->get());

            auto new_list = std::make_shared<List>();

            new_list->push_back(*this);
            new_list->insert(new_list->end(), list->begin(), list->end());

            this->value = new_list;
        }
        catch (const std::bad_variant_access& e)
        {
            std::cerr << "b is not a list\n";
        }


        return;
    }

    void prepend_to_list(Answer* b)
    {
        auto new_list = std::make_shared<List>();
        new_list->push_back(*this);

        auto b_list = std::get<std::shared_ptr<List>>(b->get());
        new_list->insert(new_list->end(), b_list->begin(), b_list->end());
        this->value = new_list;
    }

    bool operator==(const Answer& other) const
    {
        if (this->value != other.value) return false;
        return true;
    }

    bool operator<(const Answer& other) const
    {
        if (this->value < other.value) return true;
        return false;
    }
};


class Lambda
{
    private:
    //std::unordered_map<std::string> params;
    std::list<std::string> params;
    pnode body;
    //Enviroment* env;
    std::shared_ptr<Enviroment> env;

    public:

    Lambda(pnode body, std::shared_ptr<Enviroment> env)
    {
        this->params = {};
        this->body = body;
        //this->env = env;
        this->env = std::make_shared<Enviroment>(env);
    }

    Lambda(std::list<std::string> par, pnode body)
    {
        this->params = par;
        this->body = body;
    }

    pnode get_body()
    {
        return this->body;
    }

    std::shared_ptr<Enviroment> get_env()
    {
        return env;
    }

    int get_params_count()
    {
        return this->params.size();
    }

    const std::list<std::string>& get_params() const
    {
        return this->params;
    }

    void add_param(std::string param)
    {
        this->params.push_back(param);
    }

    void print()
    {
        std::cout << "Lambda: params: ";
        for (auto& i : this->params)
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
        print_tree(body, 0);
    }

    bool operator==(const Lambda& other) const
    {
        if (params != other.params) return false;
        return true;
    }
};

typedef std::map<std::string, Answer> binding_type;

class Enviroment
{
    //binding_type* bindings;
    //Enviroment* parent;

    std::shared_ptr<binding_type> bindings;
    std::shared_ptr<Enviroment> parent;

    public:

    Enviroment(std::shared_ptr<Enviroment> parent = nullptr)
    {
        // this->bindings = new binding_type();
        // this->parent = parent;

        this->bindings = std::make_shared<binding_type>();
        this->parent = parent;
    }

    void add_binding(std::string name)
    {
        this->bindings->insert({name, Answer()});
    }

    void add_binding(std::string name, Answer_Value value)
    {
        this->bindings->insert({name, value});
    }

    void set_bind(std::string name, Answer_Value value)
    {
        auto it = bindings->find(name);
        if (it != bindings->end()) it->second = value;
    }

    void bind(std::string name, Answer_Value value)
    {
        bindings->insert_or_assign(name, value);
    }

    Answer* get_bind(std::string var)
    {
        auto val = this->bindings->find(var);
        if (val != this->bindings->end()) return &val->second;
        if (this->parent) return this->parent->get_bind(var);
        return nullptr;
    }


    
};


// namespace std
// {
//     template<> 
//     struct hash<Answer>
//     {
//         size_t operator()(const Answer& a) const
//         {
//         }
//     };
// }

