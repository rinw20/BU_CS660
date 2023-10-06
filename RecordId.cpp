#include <db/RecordId.h>
#include <stdexcept>

using namespace db;

//
// RecordId
//

// TODO pa1.4: implement
RecordId::RecordId(const PageId *pid, int tupleno) {
    this->pid = pid;
    this->tupleno = tupleno;
}

bool RecordId::operator==(const RecordId &other) const {
    // TODO pa1.4: implement
    return (*this->pid == *other.pid) && (this->tupleno == other.tupleno);
}

const PageId *RecordId::getPageId() const {
    // TODO pa1.4: implement
    return this->pid;
}

int RecordId::getTupleno() const {
    // TODO pa1.4: implement
    return this->tupleno;
}

//
// RecordId hash function
//

std::size_t std::hash<RecordId>::operator()(const RecordId &r) const {
    // TODO pa1.4: implement
    size_t hash_value = 0;
    const PageId* pageid = r.getPageId();
    hash_value ^= std::hash<PageId>{}(*pageid);
    hash_value ^= std::hash<int>{}(r.getTupleno());

    return hash_value;
}
