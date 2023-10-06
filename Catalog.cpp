#include <db/Catalog.h>
#include <db/TupleDesc.h>
#include <stdexcept>

using namespace db;

void Catalog::addTable(DbFile *file, const std::string &name, const std::string &pkeyField) {
    // TODO pa1.2: implement
    if(file == nullptr){
        throw std::out_of_range("File cannot be NULL");
    }

    Table* new_table = new Table(file, name, pkeyField);
    int table_id = file->getId();
    if(this->Map_id_table.find(table_id) != this->Map_id_table.end()){
        //id already exist, the file alreay exist
        this->Map_id_table.erase(table_id);
    }
    if(this->Map_name_id.find(name) != this->Map_name_id.end()){
        //name already exists, remove the old record in map_id_table and modify the record in map_name_id
        int existed_id = this->Map_name_id[name];
        this->Map_id_table.erase(existed_id);
        //update id to the new one
        this->Map_name_id[name] = table_id;
    }else{
        //not already exists, insert a new one
        this->Map_name_id.insert(std::pair(name, table_id));
    }

    this->Map_id_table.insert(std::pair(table_id,*new_table));
}

int Catalog::getTableId(const std::string &name) const {
    // TODO pa1.2: implement
    auto it = Map_name_id.find(name);
    if(it != Map_name_id.end()){
        return it->second;
    }
    else{
        //name doesn't exist
        throw std::invalid_argument("Name doesn't exist");
    }
}

const TupleDesc &Catalog::getTupleDesc(int tableid) const {
    // TODO pa1.2: implement
    auto it = Map_id_table.find(tableid);
    if(it != Map_id_table.end()){
        return it->second.file->getTupleDesc();
    }
    else{
        throw std::runtime_error("Table doesn't exist");
    }
}

DbFile *Catalog::getDatabaseFile(int tableid) const {
    // TODO pa1.2: implement
    auto it = Map_id_table.find(tableid);
    if(it != Map_id_table.end()){
        return it->second.file;
    }
    else{
        throw std::runtime_error("Table doesn't exist");
    }
}

std::string Catalog::getPrimaryKey(int tableid) const {
    // TODO pa1.2: implement
    auto it = Map_id_table.find(tableid);
    if(it != Map_id_table.end()){
        return it->second.pkeyField;
    }
    else{
        throw std::runtime_error("Table doesn't exist");
    }
}

std::string Catalog::getTableName(int id) const {
    // TODO pa1.2: implement
    auto it = Map_id_table.find(id);
    if(it != Map_id_table.end()){
        return it->second.name;
    }
    else{
        throw std::runtime_error("Table doesn't exist");
    }
}

void Catalog::clear() {
    // TODO pa1.2: implement
    Map_id_table.clear();
    Map_name_id.clear();
}
