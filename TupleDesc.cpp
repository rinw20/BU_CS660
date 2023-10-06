#include <db/TupleDesc.h>

using namespace db;

//
// TDItem
//

bool TDItem::operator==(const TDItem &other) const {
    // TODO pa1.1: implement
    if(this->fieldType != other.fieldType || this->fieldName != other.fieldName){
        return false;
    }
    else{
        return true;
    }
}

std::size_t std::hash<TDItem>::operator()(const TDItem &r) const {
    // TODO pa1.1: implement
    std::size_t hash_value = 0;

    std::hash<Types::Type> type_hash;
    std::hash<std::string> name_hash;
    hash_value ^= type_hash(r.fieldType);
    hash_value ^= name_hash(r.fieldName);

    return hash_value;

}

//
// TupleDesc
//

// TODO pa1.1: implement
TupleDesc::TupleDesc(const std::vector<Types::Type> &types) {
    if(types.size() < 1){
        throw std::out_of_range("types must contain at least one entry");
    }
    for(size_t index = 0; index < types.size(); index++){
        TDItem tdItem(types[index], "unnamed");
        this->tdItems.push_back(tdItem);
    }
}

// TODO pa1.1: implement
TupleDesc::TupleDesc(const std::vector<Types::Type> &types, const std::vector<std::string> &names) {
    if(types.size() < 1){
        throw std::out_of_range("types must contain at least one entry");
    }
    for(size_t index = 0; index < types.size(); index++) {
        TDItem tdItem(types[index], names[index]);
        this->tdItems.push_back(tdItem);
    }
}

size_t TupleDesc::numFields() const {
    // TODO pa1.1: implement
    return this->tdItems.size();
}

std::string TupleDesc::getFieldName(size_t i) const {
    // TODO pa1.1: implement
    return this->tdItems[i].fieldName;

}

Types::Type TupleDesc::getFieldType(size_t i) const {
    // TODO pa1.1: implement
    return this->tdItems[i].fieldType;
}

int TupleDesc::fieldNameToIndex(const std::string &fieldName) const {
    // TODO pa1.1: implement
    for(int index = 0; index < this->tdItems.size(); index++){
        if(this->tdItems[index].fieldName == fieldName){
            return index;
        }
    }
    throw std::invalid_argument("Unknown Fieldname");
}

size_t TupleDesc::getSize() const {
    // TODO pa1.1: implement
    size_t tpsSize = 0;
    for(size_t index = 0; index < this->tdItems.size(); index++){
        tpsSize += getLen(this->tdItems[index].fieldType);
    }
    return tpsSize;

}

TupleDesc TupleDesc::merge(const TupleDesc &td1, const TupleDesc &td2) {
    // TODO pa1.1: implement
    std::vector<TDItem> mergedTDItems;
    for(size_t index = 0; index < td1.tdItems.size(); index++){
        mergedTDItems.push_back(td1.tdItems[index]);
    }
    for(size_t index = 0; index < td2.tdItems.size(); index++){
        mergedTDItems.push_back(td2.tdItems[index]);
    }
    TupleDesc mergedTd;
    mergedTd.tdItems = mergedTDItems;
    return mergedTd;
}

std::string TupleDesc::to_string() const {
    // TODO pa1.1: implement
    std::string string_td = "";
    for(auto it = this->begin(); it != this->end(); it++){
        string_td += it->to_string();
        //there's no comma in TDItem's to_string()
        if(std::next(it) != end()){
            string_td += ", ";
        }
    }
}

bool TupleDesc::operator==(const TupleDesc &other) const {
    // TODO pa1.1: implement
    if(this->tdItems.size() != other.tdItems.size()){
        return false;
    }
    for(size_t index = 0; index < this->tdItems.size(); index++){
        if(this->tdItems[index] != other.tdItems[index]){
            return false;
        }
    }
    return true;
}

TupleDesc::iterator TupleDesc::begin() const {
    // TODO pa1.1: implement
    return this->tdItems.begin();
}

TupleDesc::iterator TupleDesc::end() const {
    // TODO pa1.1: implement
    return this->tdItems.end();
}

std::size_t std::hash<db::TupleDesc>::operator()(const db::TupleDesc &td) const {
    // TODO pa1.1: implement
    std::size_t hash_value = 0;

    for(auto it = td.begin(); it != td.end(); it++){
        hash_value ^= std::hash<db::TDItem>{}(*it);
    }

    return hash_value;
}
