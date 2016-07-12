#include <cmath>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <bitset>
#include <fstream>
#include <cstdio>
#include <cstdint>
using namespace std;

//pragma pack(1)
class Header {
    uint16_t marker; //ST in message
    uint8_t msg_type; //1=OrderEntry, 2=OrderAck, 3=OrderFill
    uint64_t sequence; 
    uint64_t timestamp; //seconds since epoch of message
    uint8_t msg_direction; //0=to exchange, 1=from exchange
    uint16_t msg_len;  //number of bytes in message body excluding header
public:
    const uint8_t get_msg_type() const {
        return msg_type;
    }
    void load(ifstream& in) {
        in.read((char*)&marker, sizeof(marker)); 
        in.read((char*)&msg_type, sizeof(msg_type)); 
        in.read((char*)&sequence, sizeof(sequence)); 
        in.read((char*)&timestamp, sizeof(timestamp)); 
        in.read((char*)&msg_direction, sizeof(msg_direction)); 
        in.read((char*)&msg_len, sizeof(msg_len)); 
    }
    void print() const {
        char a[2];
        a[0]=marker;
        a[1]=(marker>>8);
        cout<<a[0]<<' '<<a[1]<<endl;
        
        printf("msg_type: %u\n", msg_type);
        printf("sequence: %u\n", sequence);
        printf("timestamp: %u\n", timestamp);
        printf("msg_direction: %u\n", msg_direction);
        printf("msg_len: %u\n", msg_len);
    }
};
//#pragma pack()

//#pragma pack(1)
class OrderEntryMsg {
    uint64_t price;
    uint32_t qty;
    char instrument[11];
    uint8_t side;
    uint64_t client_assigned_id;
    uint8_t time_in_force; //1=immediate or cancel (IOC), 2=Good for Day (GFD)
    char trader_tag[4];
    uint8_t firm_id;
    char firm[256+8];
    //char termination_string[8];
public:
    void load(ifstream& in) {
        in.read((char*)&price, sizeof(price)); 
        in.read((char*)&qty, sizeof(qty)); 
        in.read((char*)&instrument, 10);//sizeof(instrument)); 
        instrument[10]='\0';
        in.read((char*)&side, sizeof(side)); 
        in.read((char*)&client_assigned_id, sizeof(client_assigned_id)); 
        in.read((char*)&time_in_force, sizeof(time_in_force)); 
        in.read((char*)&trader_tag, 3);//sizeof(trader_tag)); 
        trader_tag[3]='\0';
        in.read((char*)&firm_id, sizeof(firm_id)); 
        
        size_t idx=0;
        while (in.read(&firm[idx], 1)) {
            idx+=1;
            if (strstr(firm, "DBDBDBDB")!=nullptr) {
                firm[idx]='\0';
                cout<<idx<<endl;
                break;
            }
        }
        //in.get(firm[0]);
        //in.get(firm[1]);
        //in.get(firm[2]);
        //in.get(firm[3]);
        
        //char *pch;
        //pch=strstr(firm, "DBDBDB");
        //in.read((char*)&termination_string, sizeof(termination_string)); 
    }
    void print() const {
        cout<<"\nOrderEntryMessage\n";
        printf("Price: %f\n", price/10000.0);
        printf("Qty: %u\n", qty);
        printf("Instrument: %s\n", instrument);
        printf("Side: %u\n", side);
        printf("Client Assigned ID: %u\n", client_assigned_id);
        printf("Time in force: %u\n", time_in_force);
        printf("Trader tag: %s\n", trader_tag);
        printf("Firm ID: %u\n", firm_id);
        printf("Firm: %s\n", firm);
        //printf("termination_string: %s\n", termination_string);
    }
};
//#pragma pack()

class OrderAckMsg {
    uint32_t order_id;
    uint64_t client_id;
    uint8_t order_status; //1=good, 2=reject
    uint8_t reject_code; //0=no code, 1=invalid product 2=invalid price 3=invalid qty
    char termination_string[8];
public:
    void load(ifstream& in) {
        in.read((char*)&order_id, sizeof(order_id)); 
        in.read((char*)&client_id, sizeof(client_id)); 
        in.read((char*)&order_status, sizeof(order_status));
        in.read((char*)&reject_code, sizeof(reject_code)); 
        
        //in.read(termination_string, 8);
        in.ignore(8);//???????????????????????????????
    }
    void print() const {
        cout<<"\nOrderAckMessage\n";
        printf("order_id: %u\n", order_id);
        printf("client_id: %u\n", client_id);
        printf("order_status Assigned ID: %u\n", order_status);
        printf("Time reject_code force: %u\n", reject_code);
    }
};

class OrderFillMsg {
    
    class RepeatingGroups {
        uint8_t firm_id;
        char trader_tag[4];
        uint32_t qty;
    public:
        void load(ifstream& in) {
            in.read((char*)&firm_id, sizeof(firm_id)); 
            in.read((char*)&trader_tag, 3);
            trader_tag[3]='\0';
            in.read((char*)&qty, sizeof(qty));
        }
        void print() const {
            cout<<"\nRepeatingGroups\n";
            printf("firm_id: %u\n", firm_id);
            printf("trader_tag: %s\n", trader_tag);
            printf("qty: %u\n", qty);
        }
    };

    uint32_t order_id;
    uint64_t fill_price;//divide by 10000
    uint32_t fill_qty;
    uint8_t no_of_contras; //number of repeating counter party groups
    vector<RepeatingGroups> v_repeating_groups;
    char termination_string[8];

public:
    void load(ifstream& in) {
        in.read((char*)&order_id, sizeof(order_id)); 
        in.read((char*)&fill_price, sizeof(fill_price)); 
        in.read((char*)&fill_qty, sizeof(fill_qty));
        in.read((char*)&no_of_contras, sizeof(no_of_contras)); 
        v_repeating_groups.resize(no_of_contras);
        for (size_t i=0; i<no_of_contras; ++i) {
            RepeatingGroups rg;
            rg.load(in);
            v_repeating_groups[i]=rg;
        }
        //in.read(termination_string, 8);
        in.ignore(8);//???????????????????????????????
    }
    void print() const {
        cout<<"\nOrderFillMessage\n";
        printf("order_id: %u\n", order_id);
        printf("fill_price: %f\n", fill_price/10000.0);
        printf("fill_qty: %u\n", fill_qty);
        printf("no_of_contras: %u\n", no_of_contras);
        for (size_t i=0; i<no_of_contras; ++i) {
            v_repeating_groups[i].print();
        }
    }
};

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    const char* filename="example_data_file.bin";
    std::ifstream in_stream(filename, std::ifstream::in | std::ifstream::binary);
    if (!in_stream) {
      std::cerr << "Invalid input file. Expected: ./" << filename << std::endl;
      return 1;
    }
    
    Header h;
    h.load(in_stream);
    h.print();

    OrderEntryMsg o;
    o.load(in_stream);
    o.print();

    cout<<"\n\n";
    Header h2;
    h2.load(in_stream);
    h2.print();

    cout<<"\n\n";
    OrderAckMsg oam;
    oam.load(in_stream);
    oam.print();

    cout<<"\n\n";
    Header h3;
    h3.load(in_stream);
    h3.print();

    cout<<"\n\n";
     OrderEntryMsg o2;
    o2.load(in_stream);
    o2.print();

    cout<<"\n\n";
    Header h4;
    h4.load(in_stream);
    h4.print();

    cout<<"\n\n";
    OrderAckMsg oam2;
    oam2.load(in_stream);
    oam2.print();

    cout<<"\n\n";
    Header h5;
    h5.load(in_stream);
    h5.print();

    cout<<"\n\n";
    OrderEntryMsg o3;
    o3.load(in_stream);
    o3.print();

    cout<<"\n\n";
    Header h6;
    h6.load(in_stream);
    h6.print();

    cout<<"\n\n";
    OrderAckMsg oam3;
    oam3.load(in_stream);
    oam3.print();

    cout<<"\n\n";
    Header h7;
    h7.load(in_stream);
    h7.print();
    
    cout<<"\n\n";
    OrderFillMsg ofm;
    ofm.load(in_stream);
    ofm.print();

    while (in_stream) {
        Header hh;
        hh.load(in_stream);
        hh.print();
        if (hh.get_msg_type()==1) {
            OrderEntryMsg *oemm=new OrderEntryMsg; oemm->load(in_stream); oemm->print(); cout<<"\n\n";
        }
        else if (hh.get_msg_type()==2) {
            OrderAckMsg *oamm=new OrderAckMsg; oamm->load(in_stream); oamm->print(); cout<<"\n\n";
        }
        else if (hh.get_msg_type()==3) {
            OrderFillMsg *ofmm=new OrderFillMsg; ofmm->load(in_stream); ofmm->print(); cout<<"\n\n";
        }
    }
    in_stream.close();

    return 0;
}
