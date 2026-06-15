#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

// -------------------------------------------------------
// FEATURE 1: Trie - for prefix based license title search
// -------------------------------------------------------

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEnd = false;
    string fullTitle = "";
    string publisher = "";
};

class CopyrightDirectory {
    TrieNode* root;

    void collectAll(TrieNode* node, vector<string>& result) {
        if (node->isEnd)
            result.push_back(node->fullTitle + " [" + node->publisher + "]");
        for (auto& p : node->children)
            collectAll(p.second, result);
    }

public:
    CopyrightDirectory() {
        root = new TrieNode();
    }

    void insert(string title, string pub) {
        TrieNode* curr = root;
        string lower = title;
        for (char& c : lower) c = tolower(c);
        for (char c : lower) {
            if (!curr->children.count(c))
                curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEnd = true;
        curr->fullTitle = title;
        curr->publisher = pub;
    }

    vector<string> search(string prefix) {
        TrieNode* curr = root;
        for (char& c : prefix) c = tolower(c);
        for (char c : prefix) {
            if (!curr->children.count(c))
                return {};
            curr = curr->children[c];
        }
        vector<string> result;
        collectAll(curr, result);
        return result;
    }

    void demo() {
        cout << "\n--- Copyright Directory (Trie) ---\n";
        cout << "Inserting license titles...\n";

        insert("Adobe Photoshop", "PUB-001");
        insert("Adobe Illustrator", "PUB-001");
        insert("Adobe Premiere", "PUB-001");
        insert("Autodesk Maya", "PUB-002");
        insert("Autodesk AutoCAD", "PUB-002");
        insert("Microsoft Office", "PUB-003");
        insert("Unity Pro", "PUB-004");

        cout << "\nSearching prefix 'ado':\n";
        for (auto& r : search("ado"))
            cout << "  " << r << "\n";

        cout << "\nSearching prefix 'micro':\n";
        for (auto& r : search("micro"))
            cout << "  " << r << "\n";

        cout << "\nSearching prefix 'uni':\n";
        for (auto& r : search("uni"))
            cout << "  " << r << "\n";

        cout << "\nSearching prefix 'xyz' (not found):\n";
        auto res = search("xyz");
        if (res.empty()) cout << "  No results found.\n";
    }
};

// -------------------------------------------------------
// FEATURE 2: Stack - for undo of permission changes
// -------------------------------------------------------

struct PermChange {
    string userID;
    string licenseKey;
    string oldPerm;
    string newPerm;
    string time;
};

class HistoryTracker {
    stack<PermChange> hist;

public:
    void addChange(string uid, string key, string oldP, string newP, string t) {
        hist.push({uid, key, oldP, newP, t});
        cout << "  Logged: " << uid << " | " << key << " : " << oldP << " -> " << newP << "\n";
    }

    void undo() {
        if (hist.empty()) {
            cout << "  Nothing to undo.\n";
            return;
        }
        PermChange last = hist.top();
        hist.pop();
        cout << "  Undone: " << last.userID << " | " << last.licenseKey
             << " reverted from " << last.newPerm << " back to " << last.oldPerm << "\n";
    }

    void demo() {
        cout << "\n--- History Tracker (Stack) ---\n";
        cout << "Recording permission changes...\n";

        addChange("USR-101", "LIC-AAA1", "READ", "REVOKED", "09:01");
        addChange("USR-202", "LIC-BBB2", "WRITE", "ADMIN", "09:05");
        addChange("USR-303", "LIC-CCC3", "ADMIN", "READ", "09:12");

        cout << "\nUndoing last two changes:\n";
        undo();
        undo();
        cout << "\nStack size now: " << hist.size() << "\n";
    }
};

// -------------------------------------------------------
// FEATURE 3: Queue - FIFO for update requests
// -------------------------------------------------------

struct UpdateReq {
    string reqID;
    string custID;
    string licKey;
    string type;
    string region;
};

class UpdateLine {
    queue<UpdateReq> q;

public:
    void enqueue(UpdateReq r) {
        q.push(r);
        cout << "  Queued: " << r.reqID << " | " << r.custID << " | " << r.type << " | " << r.region << "\n";
    }

    void processNext() {
        if (q.empty()) {
            cout << "  Queue is empty.\n";
            return;
        }
        UpdateReq r = q.front();
        q.pop();
        cout << "  Processed: " << r.reqID << " -> " << r.type << " for " << r.custID << "\n";
    }

    int size() { return q.size(); }

    void demo() {
        cout << "\n--- Update Line (Queue / FIFO) ---\n";
        cout << "Adding update requests from different regions...\n";

        enqueue({"REQ-001", "CUST-IN-1001", "LIC-AAA1", "RENEW", "India"});
        enqueue({"REQ-002", "CUST-US-2002", "LIC-BBB2", "TRANSFER", "USA"});
        enqueue({"REQ-003", "CUST-EU-3003", "LIC-CCC3", "REVOKE", "Europe"});
        enqueue({"REQ-004", "CUST-JP-4004", "LIC-DDD4", "RENEW", "Japan"});

        cout << "\nProcessing all in FIFO order:\n";
        while (size() > 0)
            processNext();
    }
};

// -------------------------------------------------------
// FEATURE 4: Hash Map - O(1) key verification
// -------------------------------------------------------

struct LicenseRec {
    string productName;
    string ownerID;
    string status;
    string expiry;
    double price;
};

class KeyLookup {
    unordered_map<string, LicenseRec> db;

public:
    void addKey(string key, LicenseRec rec) {
        db[key] = rec;
        cout << "  Added: " << key << " -> " << rec.productName << " (" << rec.status << ")\n";
    }

    void verify(string key) {
        if (!db.count(key)) {
            cout << "  [INVALID] Key not found: " << key << "\n";
            return;
        }
        LicenseRec& r = db[key];
        cout << "  [" << r.status << "] " << key
             << " | " << r.productName
             << " | Owner: " << r.ownerID
             << " | Expiry: " << r.expiry
             << " | $" << fixed << setprecision(2) << r.price << "\n";
    }

    void demo() {
        cout << "\n--- Key Lookup (Hash Map) ---\n";
        cout << "Registering license keys...\n";

        addKey("LIC-AAA1", {"Adobe Photoshop",   "USR-101", "ACTIVE",  "2026-12-31", 599.99});
        addKey("LIC-BBB2", {"Adobe Illustrator", "USR-202", "ACTIVE",  "2026-06-30", 499.99});
        addKey("LIC-CCC3", {"Autodesk Maya",     "USR-303", "EXPIRED", "2025-01-01", 1799.00});
        addKey("LIC-DDD4", {"Microsoft Office",  "USR-404", "ACTIVE",  "2027-03-15", 149.99});
        addKey("LIC-EEE5", {"Unity Pro",         "USR-505", "REVOKED", "2025-06-01", 399.00});

        cout << "\nVerifying keys:\n";
        verify("LIC-AAA1");
        verify("LIC-CCC3");
        verify("LIC-EEE5");
        verify("LIC-XYZ9");
    }
};

// -------------------------------------------------------
// FEATURE 5: Merge Sort - rank assets by value
// -------------------------------------------------------

struct Asset {
    string name;
    double value;
    int usage;
};

class ValueSorter {
    void mergeSort(vector<Asset>& arr, int l, int r, bool byVal) {
        if (l >= r) return;
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid, byVal);
        mergeSort(arr, mid + 1, r, byVal);

        vector<Asset> left(arr.begin() + l, arr.begin() + mid + 1);
        vector<Asset> right(arr.begin() + mid + 1, arr.begin() + r + 1);

        int i = 0, j = 0, k = l;
        while (i < (int)left.size() && j < (int)right.size()) {
            bool pickLeft = byVal ? (left[i].value >= right[j].value)
                                  : (left[i].usage  >= right[j].usage);
            arr[k++] = pickLeft ? left[i++] : right[j++];
        }
        while (i < (int)left.size())  arr[k++] = left[i++];
        while (j < (int)right.size()) arr[k++] = right[j++];
    }

public:
    void sortAndPrint(vector<Asset> arr, bool byVal) {
        if (arr.empty()) return;
        mergeSort(arr, 0, arr.size() - 1, byVal);

        string label = byVal ? "Market Value" : "Usage Count";
        cout << "  Sorted by " << label << ":\n";
        cout << "  " << left << setw(4) << "#"
             << setw(25) << "Name"
             << setw(16) << "Value ($)"
             << setw(12) << "Usage\n";
        cout << "  " << string(55, '-') << "\n";
        for (int i = 0; i < (int)arr.size(); i++) {
            cout << "  " << setw(4) << (i+1)
                 << setw(25) << arr[i].name
                 << setw(16) << fixed << setprecision(2) << arr[i].value
                 << setw(12) << arr[i].usage << "\n";
        }
    }

    void demo() {
        cout << "\n--- Value Sorter (Merge Sort) ---\n";

        vector<Asset> assets = {
            {"Adobe Photoshop",    599.99, 15420},
            {"Autodesk Maya",     1799.00,  3210},
            {"Microsoft Office",   149.99, 52300},
            {"Unity Pro",          399.00,  9870},
            {"Unreal Engine",        0.00, 18650},
            {"Adobe Illustrator",  499.99, 11200},
            {"Autodesk AutoCAD",  2190.00,  2950},
        };

        sortAndPrint(assets, true);
        cout << "\n";
        sortAndPrint(assets, false);
    }
};

// -------------------------------------------------------
// FEATURE 6: Graph - license distribution network
// -------------------------------------------------------

class LicenseNetwork {
    unordered_map<string, vector<pair<string, string>>> adj;

public:
    void addEdge(string from, string to, string rel) {
        adj[from].push_back({to, rel});
        if (!adj.count(to)) adj[to] = {};
        cout << "  " << from << " --[" << rel << "]--> " << to << "\n";
    }

    void printNetwork() {
        cout << "\n  Full network:\n";
        for (auto& [node, edges] : adj) {
            cout << "  " << node << "\n";
            for (auto& [nb, rel] : edges)
                cout << "    -> " << nb << " (" << rel << ")\n";
        }
    }

    void bfs(string start) {
        unordered_map<string, bool> visited;
        queue<string> q;
        q.push(start);
        visited[start] = true;

        cout << "\n  BFS from " << start << ": ";
        while (!q.empty()) {
            string node = q.front(); q.pop();
            cout << node << " ";
            for (auto& [nb, rel] : adj[node]) {
                if (!visited[nb]) {
                    visited[nb] = true;
                    q.push(nb);
                }
            }
        }
        cout << "\n";
    }

    void demo() {
        cout << "\n--- License Network (Graph) ---\n";
        cout << "Building creator -> publisher -> user network...\n";

        addEdge("CREATOR-Adobe",    "PUBLISHER-SoftCo",  "distributes");
        addEdge("CREATOR-Adobe",    "PUBLISHER-GameHub", "distributes");
        addEdge("CREATOR-Autodesk", "PUBLISHER-SoftCo",  "distributes");
        addEdge("PUBLISHER-SoftCo", "USER-EnterpriseA",  "licensed_to");
        addEdge("PUBLISHER-SoftCo", "USER-EnterpriseB",  "licensed_to");
        addEdge("PUBLISHER-GameHub","USER-IndividualX",  "licensed_to");

        printNetwork();
        bfs("CREATOR-Adobe");
    }
};

// -------------------------------------------------------
// FEATURE 7: BFS Shortest Path - quick verification path
// -------------------------------------------------------

class QuickCheck {
    unordered_map<string, vector<string>> graph;

public:
    void addEdge(string a, string b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    void shortestPath(string src, string dst) {
        unordered_map<string, string> parent;
        unordered_map<string, bool> visited;
        queue<string> q;

        q.push(src);
        visited[src] = true;
        parent[src] = "";

        while (!q.empty()) {
            string curr = q.front(); q.pop();
            if (curr == dst) break;
            for (auto& nb : graph[curr]) {
                if (!visited[nb]) {
                    visited[nb] = true;
                    parent[nb] = curr;
                    q.push(nb);
                }
            }
        }

        if (!visited.count(dst)) {
            cout << "  No path found from " << src << " to " << dst << "\n";
            return;
        }

        vector<string> path;
        for (string at = dst; at != ""; at = parent[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        cout << "  Path from " << src << " to " << dst << ": ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i];
            if (i + 1 < (int)path.size()) cout << " -> ";
        }
        cout << "\n  Hops: " << path.size() - 1 << "\n";
    }

    void demo() {
        cout << "\n--- Quick Check (BFS Shortest Path) ---\n";
        cout << "Building verification node network...\n";

        addEdge("CLIENT",   "NODE-MUM");
        addEdge("NODE-MUM", "NODE-DEL");
        addEdge("NODE-MUM", "NODE-SG");
        addEdge("NODE-DEL", "NODE-LON");
        addEdge("NODE-SG",  "NODE-LON");
        addEdge("NODE-LON", "REGISTRY");
        addEdge("NODE-DEL", "REGISTRY");

        cout << "\n";
        shortestPath("CLIENT", "REGISTRY");
        shortestPath("NODE-MUM", "REGISTRY");
        shortestPath("NODE-DEL", "NODE-SG");
    }
};

// -------------------------------------------------------
// FEATURE 8: Greedy - bundle discount optimizer
// -------------------------------------------------------

struct Bundle {
    string name;
    double price;
    double value;
};

class DiscountPlanner {
public:
    void plan(vector<Bundle> bundles, double budget) {
        // sort by value/price ratio descending (greedy choice)
        sort(bundles.begin(), bundles.end(), [](Bundle& a, Bundle& b) {
            return (a.value / a.price) > (b.value / b.price);
        });

        double totalVal = 0;
        double remaining = budget;

        cout << "  Budget: $" << fixed << setprecision(2) << budget << "\n\n";
        cout << "  " << left << setw(35) << "Bundle"
             << setw(12) << "Price"
             << setw(12) << "Value"
             << "Decision\n";
        cout << "  " << string(68, '-') << "\n";

        for (auto& b : bundles) {
            cout << "  " << setw(35) << b.name
                 << setw(12) << fixed << setprecision(2) << b.price
                 << setw(12) << b.value;

            if (remaining >= b.price) {
                remaining -= b.price;
                totalVal += b.value;
                cout << "SELECTED\n";
            } else if (remaining > 0) {
                double frac = remaining / b.price;
                totalVal += frac * b.value;
                cout << "PARTIAL (" << (int)(frac * 100) << "%)\n";
                remaining = 0;
            } else {
                cout << "SKIPPED\n";
            }
        }

        cout << "\n  Total value acquired: $" << fixed << setprecision(2) << totalVal << "\n";
    }

    void demo() {
        cout << "\n--- Discount Planner (Greedy) ---\n";
        cout << "Optimizing corporate bundle purchase...\n\n";

        vector<Bundle> bundles = {
            {"Adobe Creative Cloud (5 seats)", 2499.00, 5800.00},
            {"Microsoft 365 Business (10)",    1200.00, 3200.00},
            {"Autodesk Industry Bundle",        3200.00, 6100.00},
            {"Unity Pro Team (3 seats)",        1197.00, 2800.00},
            {"JetBrains All Products (3)",       699.00, 2100.00},
            {"GitHub Enterprise (10 seats)",     950.00, 2400.00},
        };

        plan(bundles, 5000.00);
    }
};

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------

int main() {
    cout << "================================\n";
    cout << " KeyVault - License Registry\n";
    cout << " ITM Skills University | Sem II\n";
    cout << " DSA with C++\n";
    cout << "================================\n";

    CopyrightDirectory trie;
    HistoryTracker     hist;
    UpdateLine         updateLine;
    KeyLookup          keyLookup;
    ValueSorter        sorter;
    LicenseNetwork     network;
    QuickCheck         qcheck;
    DiscountPlanner    planner;

    int choice;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Copyright Directory  (Trie)\n";
        cout << "2. History Tracker      (Stack)\n";
        cout << "3. Update Line          (Queue)\n";
        cout << "4. Key Lookup           (Hash Map)\n";
        cout << "5. Value Sorter         (Merge Sort)\n";
        cout << "6. License Network      (Graph)\n";
        cout << "7. Quick Check          (BFS)\n";
        cout << "8. Discount Planner     (Greedy)\n";
        cout << "9. Run All\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: trie.demo();       break;
            case 2: hist.demo();       break;
            case 3: updateLine.demo(); break;
            case 4: keyLookup.demo();  break;
            case 5: sorter.demo();     break;
            case 6: network.demo();    break;
            case 7: qcheck.demo();     break;
            case 8: planner.demo();    break;
            case 9:
                trie.demo();
                hist.demo();
                updateLine.demo();
                keyLookup.demo();
                sorter.demo();
                network.demo();
                qcheck.demo();
                planner.demo();
                break;
            case 0:
                cout << "Exiting.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
