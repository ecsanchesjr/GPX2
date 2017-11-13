#ifndef PARTITION_H
#define PARTITION_H

#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <tuple>

using std::string;
using std::vector;
using std::ostream;
using std::endl;
using std::pair;
using std::set;
using std::tuple;
using std::get;

class Partition {

    friend ostream& operator<<(ostream&, const Partition&);

public:
    using ConnectionPairVector = vector<pair<int, int>>;
    //id da partição conectada, id do nó que liga e o id do nó que está ligado
    // using ConnectedNode = vector<pair<int, pair<string, string>>>;
    using ConnectedNode = vector<tuple<int, string, string>>;

    Partition();
    Partition(const int, vector<string>, vector<string>);

    vector<string>& getNodes();
    vector<string>& getAccessNodes();
    ConnectedNode& getConnectedTo();
    ConnectionPairVector& getConnections();
    vector<pair<string,string>> getEntryAndExits();
    int getId();

    void setId(const int);
    void setNodes(vector<string>&);
    void setAccessNodes(vector<string>&);
    void setConnectedTo(ConnectedNode&);
    void setConnections(ConnectionPairVector);
    void setEntryAndExits(vector<pair<string,string>>);

private:
    int id;
    vector<string> nodes;
    vector<string> accessNodes;
    vector<pair<string,string>> entryAndExits;

    //variáveis apenas utilizadas na fusion
    ConnectedNode connectedTo;
    ConnectionPairVector connections;
};

#endif