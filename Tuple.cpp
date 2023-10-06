#include <db/Tuple.h>
#include <iostream>

using namespace db;

//
// Tuple
//

// TODO pa1.1: implement
Tuple::Tuple(const TupleDesc &td, RecordId *rid) {
    this->td = td;
    this->rid = rid;
    std::vector<const Field *>* temp = new std::vector<const Field*>(td.numFields());
    this->fields = *temp;
}

const TupleDesc &Tuple::getTupleDesc() const {
    // TODO pa1.1: implement
    return this->td;
}

const RecordId *Tuple::getRecordId() const {
    // TODO pa1.1: implement
    return this->rid;
}

void Tuple::setRecordId(const RecordId *id) {
    // TODO pa1.1: implement
    this->rid = id;
}

const Field &Tuple::getField(int i) const {
    // TODO pa1.1: implement
    if(i < 0 || i >= fields.size()){
        throw std::out_of_range("Invalid Field index");
    }
    else{
        const Field* fieldptr = this->fields[i];
        return *fieldptr;
    }
}

void Tuple::setField(int i, const Field *f) {
    // TODO pa1.1: implement

    if( i >=0 && i < this->fields.size()){
        this->fields[i] = f;
    }
//    else {
//        throw std::out_of_range("Invalid field index");
//    }
}

Tuple::iterator Tuple::begin() const {
    // TODO pa1.1: implement
    return this->fields.begin();
}

Tuple::iterator Tuple::end() const {
    // TODO pa1.1: implement
    return this->fields.end();
}

std::string Tuple::to_string() const {
    // TODO pa1.1: implement
    std::string string_fields="";
    for(auto it = this->begin(); it!=this->end(); ++it){
        string_fields += (*it)->to_string();
        if(std::next(it) != end()){
            string_fields += ", ";
        }
    }
    return string_fields;
}
