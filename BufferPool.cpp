#include <db/BufferPool.h>
#include <db/Database.h>

using namespace db;

// TODO pa1.3: implement
BufferPool::BufferPool(int numPages) {
    this->maxPages = numPages;
}

Page *BufferPool::getPage(const TransactionId &tid, PageId *pid) {
    // TODO pa1.3: implement
    //already in buffer
    if(poolMap.find(pid)!=poolMap.end()){
        return poolMap[pid];
    }
    else{
//        Catalog c;
//        c = Database::getCatalog();
        DbFile* file = Database::getCatalog().getDatabaseFile(pid->getTableId());
        Page* p = file->readPage(*pid);
        this->poolMap.insert(std::pair(pid, p));
        return p;
    }
}

void BufferPool::evictPage() {
    // do nothing for now
}
