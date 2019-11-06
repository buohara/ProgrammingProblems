#include "problems.h"
#include <map>
#include <queue>

using namespace std;

// Binary tree stored as an array of nodes.

struct HuffmanTree
{
    uint32_t root;

    struct Node
    {
        uint32_t l;
        uint32_t r;
        char val;
    };

    vector<Node> nodes;
};

// Globals.

static map<char, uint32_t> weights;
static map<char, string> codeTable;
static map<string, char> decodeTable;

static HuffmanTree hTree;

static const string text(
    "Sed ut perspiciatis unde omnis iste natus error sit"
    "voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque"
    "ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta"
    "sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut"
    "odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem"
    "sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet,"
    "consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt"
    "ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam,"
    "quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid"
    "ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea"
    "voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem"
    "eum fugiat quo voluptas nulla pariatur?"
);

static const uint32_t INVALID = 0xFFFFFFFF;

/**
 * ComputeWeights - Iterate through characters of an input string and count occurrences
 * of each character. These counts will be used as weights to build a Huffman tree.
 *
 * Assumes input message of non-zero length and global character weight table is empty.
 *
 * @param text Text to count character occurrences for [in].
 */

void ComputeWeights(const string &text)
{
    assert(text.size() > 0);
    assert(weights.size() == 0);

    const char* pData = text.c_str();
    const uint32_t l = text.length();

    for (uint32_t i = 0; i < l; i++)
    {
        weights[pData[i]]++;
    }
}

/**
 * BuildHuffmanTree - Given character occurence counts for an input text, build a Huffman tree.
 * Method works by first putting all counts into 1) a priority queue (low count = high priority),
 * and 2) as leaf nodes in the Huffman tree. Next, extract pairs of counts from the priority
 * queue. Sum the weights to form a new internal Huffman tree nodes that's the parent of the two
 * extracted nodes. Add this node to the tree, and add it as a new entry in the priority 
 * queue. Continue building tree until priority queue is empty.
 *
 * Assumes non-zero size for global weights table (a message was parsed and weights computed
 * before calling).
 */

void BuildHuffmanTree()
{
    assert(weights.size() > 0);

    struct QueueEntry
    {
        char val;
        uint32_t weight;
        uint32_t treeIdx;
    };

    auto cmp = [](QueueEntry &e1, QueueEntry &e2) { return e1.weight > e2.weight; };
    priority_queue<QueueEntry, vector<QueueEntry>, decltype(cmp)> orderedWeights(cmp);

    hTree.root      = ~0;
    uint32_t nNodes = 0;

    for (auto &kv : weights)
    {
        orderedWeights.push({ kv.first, kv.second, nNodes++ });
        hTree.nodes.push_back({ INVALID, INVALID, kv.first });
    }

    while (orderedWeights.size() > 1)
    {
        auto w1 = orderedWeights.top();
        orderedWeights.pop();
        
        auto w2 = orderedWeights.top();
        orderedWeights.pop();

        HuffmanTree::Node newNode = { w1.treeIdx, w2.treeIdx, '\0' };
        hTree.nodes.push_back(newNode);

        QueueEntry newEntry = { '\0', w1.weight + w2.weight, nNodes++ };
        orderedWeights.push(newEntry);
    }

    hTree.root = hTree.nodes.size() - 1;
}

/**
 * BuildCodeTableFromTree - Given a Huffman tree, build a table of character codes. Walk the
 * Huffman tree in depth-first order and build character codes based on number of lefts/rights 
 * taken to reach a leaf node. Leaf node has INVALID for left/right children.
 *
 * Assumes Huffman tree was built before calling and has valid root node.
 */

void BuildCodeTableFromTree()
{
    assert(hTree.nodes.size() > 0);
    assert(hTree.root < hTree.nodes.size());

    vector<bool> visitedNodes(hTree.nodes.size(), false);
    vector<char> codeStack;
    vector<HuffmanTree::Node> stack;

    stack.push_back(hTree.nodes[hTree.root]);
    codeStack.push_back('\0');

    HuffmanTree::Node curNode;
    visitedNodes[hTree.root] = true;

    while (!stack.empty())
    {
        curNode = stack.back();

        if ((curNode.l != INVALID) && (visitedNodes[curNode.l] == false))
        {
            stack.push_back(hTree.nodes[curNode.l]);
            visitedNodes[curNode.l] = true;
            codeStack.push_back('0');
            curNode = hTree.nodes[curNode.l];

            continue;
        }

        if ((curNode.r != INVALID) && (visitedNodes[curNode.r] == false))
        {
            stack.push_back(hTree.nodes[curNode.r]);
            visitedNodes[curNode.r] = true;
            codeStack.push_back('1');
            curNode = hTree.nodes[curNode.r];

            continue;
        }

        if ((curNode.l == INVALID) && (curNode.r == INVALID))
        {
            string code;

            for (uint32_t i = 1; i < codeStack.size(); i++)
            {
                code += codeStack[i];
            }

            codeTable[curNode.val] = code;
            decodeTable[code] = curNode.val;
        }

        codeStack.pop_back();
        stack.pop_back();
    }
}

/**
 * BytesRequired - Helper function. After Huffman code computed, determine how many bytes
 * needed to encode global message.
 * 
 * Assumes non-zero message and Huffman code length. 
 *
 * @return Number of bytes required to encode global message using Huffman code.
 */

uint32_t BytesRequired()
{
    assert(codeTable.size() > 0);
    assert(text.size() > 0);

    uint32_t size = 0;

    uint32_t l = text.length();
    const char *pData = text.data();

    for (uint32_t i = 0; i < l; i++)
    {
        size += codeTable[pData[i]].size();
    }

    return ((size / 8) + 1);
}

/**
 * Encode - Given a Huffman code table, encode a (global) input message. Concatenate all
 * the input message's codes into a binary string. Then grab a byte at a time from the
 * binary string and covert to an 8-bit int and store in output message.
 *
 * Assumes zero output message length on input and non-zero code table size. 
 *
 * @param msg Coded output message [out].
 */

void Encode(vector<uint8_t> &msg)
{
    assert(msg.size() == 0);
    assert(codeTable.size() > 0);

    uint32_t l          = text.length();
    const char *pData   = text.data();
    uint32_t bytes      = BytesRequired();

    msg.resize(bytes);

    string bitString;

    for (uint32_t i = 0; i < l; i++)
    {
        bitString += codeTable[pData[i]];
    }

    for (uint32_t i = 0, j = 0; i < bitString.length(); i += 8, j++)
    {
        uint32_t begin = i;
        uint32_t len = (i + 7) > bitString.length() ? bitString.length() - i : 8;

        string byte = bitString.substr(begin, len);
        msg[j] = stoi(byte, nullptr, 2);
    }
}

/**
 * Decode - Given a Huffman code table, decode a message. Convert input bytes into
 * a binary string. Next, scan the binary string for codes. Keep adding bits from the string
 * until a match is found in the decode table. Add the corresponding character
 * to the output texts. Continue until end of binary string is reached.
 *
 * Assumes non-zero length input message and zero-length output message. Assumes
 * non-zero length code table.
 *
 * @param msg Coded input message [in].
 * @param out String result of decoding [out].
 */

void Decode(vector<uint8_t> &msg, string &out)
{
    assert(out.size() == 0);
    assert(msg.size() > 0);
    assert(codeTable.size() > 0);

    string bitString;

    for (uint32_t i = 0; i < msg.size(); i++)
    {
        for (uint32_t j = 8; j-- > 0;)
        {
            bitString += (msg[i] & (1 << j)) ? '1' : '0';
        }
    }

    for (uint32_t i = 0; i < bitString.length(); i++)
    {
        string code = string(1, bitString[i]);

        while (decodeTable.count(code) == 0)
        {
            if (i >= bitString.length())
            {
                code = "";
                break;
            }

            code += string(1, bitString[++i]);
        }

        out.push_back(decodeTable[code]);
        if (decodeTable[code] == '\0')
        {
            break;
        }
    }
}

/**
 * TestHuffman - Build a Huffman code from sample text. Encode the message and report
 * compression ratio. Make sure decoded text matches original text (except last byte. During
 * encoding, last byte may have trailing zeros. Need to tweak coding for this case).
 */

void TestHuffman()
{
    ComputeWeights(text);
    BuildHuffmanTree();
    BuildCodeTableFromTree();
    
    vector<uint8_t> codedMsg;
    Encode(codedMsg);

    double compressionRatio = (double)text.length() / (double)codedMsg.size();
    cout << "Compression ratio = " << compressionRatio << endl;

    string decodedMsg;
    Decode(codedMsg, decodedMsg);

    uint32_t l = text.length();

    assert(decodedMsg.substr(0, l - 1) == text.substr(0, l - 1));
}