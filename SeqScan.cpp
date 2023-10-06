#include <db/SeqScan.h>


using namespace db;

// TODO pa1.6: implement
SeqScan::SeqScan(TransactionId *tid, int tableid, const std::string &tableAlias) {
    this->tid = tid;
    this->tableId = tableid;
    this->tableAlias = tableAlias;
}

std::string SeqScan::getTableName() const {
    // TODO pa1.6: implement
    return Database::getCatalog().getTableName(this->tableId);
}

std::string SeqScan::getAlias() const {
    // TODO pa1.6: implement
    return this->tableAlias;
}

void SeqScan::reset(int tabid, const std::string &tableAlias) {
    // TODO pa1.6: implement
    this->tableId = tabid;
    this->tableAlias = tableAlias;
}

const TupleDesc &SeqScan::getTupleDesc() const {
    // TODO pa1.6: implement
    return Database::getCatalog().getTupleDesc(this->tableId);
}

SeqScan::iterator SeqScan::begin() const {
    // TODO pa1.6: implement
    std::string tablename = this->getTableName();
    int tableid = Database::getCatalog().getTableId(tablename);
    DbFile* file = Database::getCatalog().getDatabaseFile(tableid);
    const HeapFile* hpfile = dynamic_cast<HeapFile*>(file);
    auto it = new HeapFileIterator(hpfile->begin());
    return SeqScanIterator(it);
}

SeqScan::iterator SeqScan::end() const {
    std::string tablename = this->getTableName();
    int tableid = Database::getCatalog().getTableId(tablename);
    DbFile* file = Database::getCatalog().getDatabaseFile(tableid);
    const HeapFile* hpfile = dynamic_cast<HeapFile*>(file);
    auto it = new HeapFileIterator(hpfile->end());
    return SeqScanIterator(it);
}

//
// SeqScanIterator
//

// TODO pa1.6: implement
SeqScanIterator::SeqScanIterator(/* TODO pa1.6: add parameters */HeapFileIterator *it) {
    this->it = it;
}

bool SeqScanIterator::operator!=(const SeqScanIterator &other) const {
    // TODO pa1.6: implement
    return *it != *other.it;
}

SeqScanIterator &SeqScanIterator::operator++() {
    // TODO pa1.6: implement
    ++(*this->it);
    return *this;
}

const Tuple &SeqScanIterator::operator*() const {
    // TODO pa1.6: implement
    return *(*this->it);
}
