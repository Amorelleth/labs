#include <iostream>
#include "array-sequence.hpp"
#include "list-sequence.hpp"

void PrintFailed(std::string testName, int expected, int got) {
    std::cout << testName << " test failed EXPECTED " << expected << " GOT " << got << std::endl;
}
void PrintFailed(std::string testName, std::string expected, int got) {
    std::cout << testName << " test failed EXPECTED " << expected << " GOT " << got << std::endl;
}
void PrintFailed(std::string testName, std::string expected, std::string got) {
    std::cout << testName << " test failed EXPECTED " << expected << " GOT " << got << std::endl;
}
void PrintFailed(std::string testName, std::string expected, Sequence<int>* got) {
    std::cout << testName << " test failed EXPECTED " << expected << " GOT " << *got << std::endl;
}
Sequence<int>* CreateSeqFromType(std::string type) {
    if (type == "array") {
        return new ArraySequence<int>;
    } else {
        return new ListSequence<int>;
    }
}

bool AppendAndGetLastTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);

    seq->Append(1);
    if (seq->GetLast() != 1) {
        PrintFailed("AppendAndGetLast To Empty", 1, seq->GetLast());
        return false;
    }
    seq->Append(2);
    if (seq->GetLast() != 2) {
        PrintFailed("AppendAndGetLast", 2, seq->GetLast());
        return false;
    }
    return true;
}

bool PrependAndGetFirstTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);

    seq->Prepend(1);
    if (seq->GetFirst() != 1) {
        PrintFailed("PrependAndGetFirst To Empty", 1, seq->GetFirst());
        return false;
    }
    seq->Prepend(2);
    if (seq->GetFirst() != 2) {
        PrintFailed("PrependAndGetFirst", 2, seq->GetFirst());
        return false;
    }
    return true;
}

bool InsertAtAndGetTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);

    seq->InsertAt(0, 1);
    seq->InsertAt(1, 2);
    seq->InsertAt(2, 3);

    if (seq->Get(0) != 1) {
        PrintFailed("InsertAtAndGet Get(0)", 1, seq->Get(0));
        return false;
    }
    if (seq->Get(1) != 2) {
        PrintFailed("InsertAtAndGet Get(1)", 2, seq->Get(1));
        return false;
    }
    if (seq->Get(2) != 3) {
        PrintFailed("InsertAtAndGet Get(2)", 3, seq->Get(2));
        return false;
    }
    return true;
}

bool GetSubsequenceTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);
    seq->Append(1);
    seq->Append(2);
    seq->Append(3);
    seq->Append(4);
    seq->Append(5);
   
    auto newSeq = seq->GetSubsequence(1, 2);
    if (newSeq->GetLength() != 2) {
        PrintFailed("GetSubsequence GetLength", 2, newSeq->GetLength());
        return false;
    }
    if (newSeq->GetFirst() != 2) {
        PrintFailed("GetSubsequence GetFirst", 2, newSeq->GetFirst());
        return false;
    }
    if (newSeq->GetLast() != 3) {
        PrintFailed("GetSubsequence GetLast", 3, newSeq->GetLast());
        return false;
    }
    return true;
}

bool RemoveTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);

    try {
        seq->Remove(999);
    } catch(...) {
        PrintFailed("RemoveTest From Empty", "nothing", "exception");
        return false;
    }

    seq->Append(4);
    seq->Append(5);
    seq->Append(6);
    seq->Remove(4);

    if (seq->GetLength() != 2 || seq->GetFirst() != 5) {
        PrintFailed("RemoveTest", "4 deleted", seq);
        return false;
    }
    return true;
}

bool GetIsEmptyTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);
    if (!seq->GetIsEmpty()) {
        PrintFailed("GetIsEmpty", "true", "false");
        return false;
    }
    seq->Append(9);
    if (seq->GetIsEmpty()) {
        PrintFailed("GetIsEmpty", "false", "true");
        return false;
    }
    return true;
}

bool GetLengthTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);
    if (seq->GetLength() != 0) {
        PrintFailed("GetLength From Empty", 0, seq->GetLength());
        return false;
    }
    seq->Append(9);
    if (seq->GetLength() != 1) {
        PrintFailed("GetLength", 1, seq->GetLength());
        return false;
    }
    return true;
}

bool MainTest(std::string type) {
    Sequence<int>* seq = CreateSeqFromType(type);

    if (seq->GetLength() != 0) {
        PrintFailed("MainTest GetLength", 0, seq->GetLength());
        return false;
    }
    seq->Append(23);
    if (seq->GetLength() != 1) {
        PrintFailed("MainTest GetLength", 1, seq->GetLength());
        return false;
    }
    if (seq->GetFirst() != 23) {
        PrintFailed("MainTest GetFirst", 23, seq->GetFirst());
        return false;
    }
    if (seq->GetLast() != 23) {
        PrintFailed("MainTest GetLast", 23, seq->GetLast());
        return false;
    }
    if (seq->Get(0) != 23) {
        PrintFailed("MainTest Get(0)", 23, seq->Get(0));
        return false;
    }
    try {
        int a = seq->Get(1);
        PrintFailed("MainTest Get(1)", "exception", seq->Get(1));
        return false;
    } catch(...) {}
    try {
        int a = seq->Get(-1);
        PrintFailed("MainTest Get(-1)", "exception", seq->Get(-1));
        return false;
    } catch(...) {}
    
    seq->Append(43);

    if (seq->GetLength() != 2) {
        PrintFailed("MainTest GetLength", 2, seq->GetLength());
        return false;
    }
    if (seq->GetFirst() != 23) {
        PrintFailed("MainTest GetFirst", 23, seq->GetFirst());
        return false;
    }
    if (seq->GetLast() != 43) {
        PrintFailed("MainTest GetLast", 43, seq->GetLast());
        return false;
    }
    if (seq->Get(0) != 23) {
        PrintFailed("MainTest Get(0)", 23, seq->Get(0));
        return false;
    }
    if (seq->Get(1) != 43) {
        PrintFailed("MainTest Get(1)", 43, seq->Get(1));
        return false;
    }

    try {
        int a = seq->Get(2);
        std::cout << "1" << a << std::endl;
    } catch(...) {}
    
    seq->Prepend(53);

    if (seq->GetLength() != 3) {
        PrintFailed("MainTest GetLength", 3, seq->GetLength());
        return false;
    }
    if (seq->GetFirst() != 53) {
        PrintFailed("MainTest GetFirst", 53, seq->GetFirst());
        return false;
    }
    if (seq->GetLast() != 43) {
        PrintFailed("MainTest GetLast", 43, seq->GetLast());
        return false;
    }
    if (seq->Get(0) != 53) {
        PrintFailed("MainTest Get(0)", 53, seq->Get(0));
        return false;
    }
    if (seq->Get(1) != 23) {
        PrintFailed("MainTest Get(1)", 23, seq->Get(1));
        return false;
    }

    try {
        int a = seq->Get(-1);
        std::cout << "1" << a << std::endl;
    } catch(...) {}
    
    try {
        int a = seq->Get(3);
        PrintFailed("MainTest Get(3)", "exception", seq->Get(3));
    } catch(...) {}

    auto newSeq = seq->GetSubsequence(1, 1);

    if (newSeq->GetLength() != 1) {
        PrintFailed("MainTest GetLength", 1, seq->GetLength());
        return false;
    }
    if (newSeq->GetFirst() != 23) {
        PrintFailed("MainTest GetFirst", 23, seq->GetFirst());
        return false;
    }
    if (newSeq->GetLast() != 23) {
        PrintFailed("MainTest GetLast", 23, seq->GetLast());
        return false;
    }

    return true;
}


int main() {
    int resArr = 0;
    int resList = 0;

    resArr += AppendAndGetLastTest("array");
    resArr += PrependAndGetFirstTest("array");
    resArr += InsertAtAndGetTest("array");
    resArr += GetSubsequenceTest("array");
    resArr += RemoveTest("array");
    resArr += GetIsEmptyTest("array");
    resArr += GetLengthTest("array");
    resArr += MainTest("array");
    std::cout << resArr;

    resList += AppendAndGetLastTest("list");
    resList += PrependAndGetFirstTest("list");
    resList += InsertAtAndGetTest("list");
    resList += GetSubsequenceTest("list");
    resList += RemoveTest("list");
    resList += GetIsEmptyTest("list");
    resList += GetLengthTest("list");
    resList += MainTest("list");
    std::cout << resList;

    return 0;
}
