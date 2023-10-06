#include <db/HeapFile.h>
#include <db/TupleDesc.h>
#include <db/Page.h>
#include <db/PageId.h>
#include <db/HeapPage.h>
#include <stdexcept>
#include <sys/stat.h>
#include <fcntl.h>

using namespace db;

//
// HeapFile
//

// TODO pa1.5: implement
HeapFile::HeapFile(const char *fname, const TupleDesc &td) {
    this->fname = fname;
    this->td = td;
    FILE* file = fopen(fname, "rb");
    if(file == nullptr){
        throw std::runtime_error("File is empty");
    }
    fclose(file);

}

int HeapFile::getId() const {
    // TODO pa1.5: implement
    return hash_value(std::filesystem::absolute(this->fname));
}

const TupleDesc &HeapFile::getTupleDesc() const {
    // TODO pa1.5: implement
    return this->td;
}

Page *HeapFile::readPage(const PageId &pid) {
    // TODO pa1.5: implement
    int pageSize = Database::getBufferPool().getPageSize();
    int offset = pid.pageNumber() * pageSize;
    FILE* file = fopen(this->fname, "rb");
    if(file == nullptr){
        throw std::runtime_error("empty file");
    }
    if(fseek(file, offset, SEEK_SET)!=0){
        fclose(file);
        throw std::runtime_error("XXX");
    }
    std::vector<uint8_t> filebuffer(pageSize);
    fread(filebuffer.data(), 1, pageSize, file);
    fclose(file);
    //trans dataType
    const HeapPageId* heapPageId = dynamic_cast<const HeapPageId*>(&pid);
    HeapPage* hp = new HeapPage(*heapPageId, filebuffer.data());
    return hp;
}

int HeapFile::getNumPages() const{
    // TODO pa1.5: implement
    int pageSize = Database::getBufferPool().getPageSize();
    long fileSize = 0;
    FILE* file = fopen(fname, "rb");
    if(file == nullptr){
        throw std::runtime_error("empty file");
    }
    if(file != nullptr){
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);
    }
    fclose(file);
    return (int)ceil(fileSize / pageSize);
}

HeapFileIterator HeapFile::begin() const {
    // TODO pa1.5: implement
    return HeapFileIterator(this, 0);
}

HeapFileIterator HeapFile::end() const {
    // TODO pa1.5: implement
    return HeapFileIterator(this, this->getNumPages());
}

//
// HeapFileIterator
//

// TODO pa1.5: implement
HeapFileIterator::HeapFileIterator(/* TODO pa1.5: add parameters */ const HeapFile* heapfile, int i) {
    this->heapfile = heapfile;
    this->pageNum = heapfile->getNumPages();
    int hfid = this->heapfile->getId();
    for (this->currentPage = i; currentPage < this->pageNum; currentPage++) {
//        HeapPageId HPid(hfid, currentPage);
//        PageId* pageId = new HeapPageId(hfid, currentPage);
//        Page* page = Database::getBufferPool().getPage({}, pageId);
//        HeapPage* currentHP = new HeapPage(HPid, static_cast<uint8_t*>(page->getPageData()));
        auto HPid = new HeapPageId (hfid, currentPage);
        Page* page = Database::getBufferPool().getPage({}, HPid);
        HeapPage *currentHP = dynamic_cast<HeapPage *>(page);
        this->it = new HeapPageIterator(currentHP->begin());
        if (*it != currentHP->end()) return;
    }
}

bool HeapFileIterator::operator!=(const HeapFileIterator &other) const {
    // TODO pa1.5: implement
    return currentPage != other.currentPage || heapfile->getId() != other.heapfile->getId();
}

Tuple &HeapFileIterator::operator*() const {
    // TODO pa1.5: implement
    return *(*it);
}

HeapFileIterator &HeapFileIterator::operator++() {
    // TODO pa1.5: implement
    ++(*this->it);
    int hfid = this->heapfile->getId();
    auto HPid = new HeapPageId(hfid, currentPage);
    Page* page = Database::getBufferPool().getPage({}, HPid);
    auto *currentHP = dynamic_cast<HeapPage *>(page);
//    HeapPage* currentHP = new HeapPage(HPid, static_cast<uint8_t*>(page->getPageData()));
    if (*this->it != currentHP->end()) return *this;

    currentPage++;
    while (currentPage < pageNum) {
        std::cout<<"currentPage is :"<<currentPage<<std::endl;
        HeapPageId hPid(hfid, currentPage);
        HPid = new HeapPageId(hfid, currentPage);
        page = Database::getBufferPool().getPage({}, HPid);
        currentHP = dynamic_cast<HeapPage *>(page);
        std::cout << currentHP->getNumTuples() << std::endl;
        this->it = new HeapPageIterator(currentHP->begin());
        if(*this->it != currentHP->end()){
            return *this;
        }
        currentPage++;
    }
    return *this;
}
