#pragma once

#include <unordered_map>

#include "object.hpp"

template <typename TableType = Object>
class ObjectTable{
    private:
        std::unordered_map<std::string, TableType> table;

    public:
        ObjectTable(){

        }

        std::unordered_map<std::string, TableType> getTable(){
            return table;
        }

        void add(TableType obj){
            table[obj.getName()] = obj;
        }


        void add(std::string name, TableType obj){
            obj.setName(name);
            table[name] = obj;
        }

        void add(const char* name, TableType obj){
            obj.setName(name);
            std::string name_string = name;
            table[name_string] = obj;
        }

        TableType get(std::string name){
            return table[name];
        }

        void update(TableType obj){
            table[obj.getName()] = obj;
        }

        void update(std::string name, TableType obj){
            obj.setName(name);
            table[name] = obj;
        }

        TableType updateAndGet(TableType obj){
            table[obj.getName()] = obj;
            return obj;
        }

        TableType updateAndGet(std::string name, TableType obj){
            obj.setName(name);
            table[name] = obj;
            return obj;
        }

        void dump(){
            // std::cout<<"\n\n########BEGIN OBJECT_TABLE#########\n";
            for(auto pair : table){
                std::cout<<"* ";
                pair.second.dump();
                std::cout<<"\n";
            }
            // std::cout<<"\n\n########END OBJECT_TABLE#########\n";
        }

        bool isKnown(std::string name){
            return (table.count(name) > 0);
        }
};