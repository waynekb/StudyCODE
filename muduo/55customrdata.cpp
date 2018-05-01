#include <vector>
#include <map>

using namespace std;

typedef map<string,vector<pair<string,int>>> map;

class customerdata{
public:
    customerdata():data_(new map){}
    int query(const string& customer,const string& stock)const;
private:
    typedef pair<string,int> entry;
    typedef vector<entry> entrylist;
    typedef map<string,entrylist> map;
    typedef shared_ptr<map> mapptr;
    void update(const string& customer,const entrylist& entrise);
    
    static int findentry(const entrylist& entries, const string& stock);

    mapptr getdata()const{
        lock_guard lock(mtx);
        return data_;
    }
    mutable mutex mtx;
    mapptr data_;
};


int customer::query(const string& customer,const string& stock)const{
    mapptr data=getdata();
    map::const_iterator entries=data->find(customer);
    if(entries!=data->end())
        return findentry(entries->second,stock);
    else 
        return -1;
}

void customer::update(const string& customer,const entrylist& entries){
    lock_guard lock(mtx);
    if(!data_.unique()){
        data_.reset(new mapptr(*mapptr));
    }
    assert(data_.unique());
    (*data_)[customer]=entries;
}
