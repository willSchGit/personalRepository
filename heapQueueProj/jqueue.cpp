// CMSC 341 - Spring 2020 - Project 4
// JQueue: a job queue using a skew heap and function pointers

#include "jqueue.h"

using std::cout;
using std::endl;
using std::domain_error;

JQueue::JQueue(prifn_t priFn) {
    _heap = nullptr;
    _size = 0;
    priority = priFn;
}

JQueue::~JQueue() {
    clear();
}

JQueue::JQueue(const JQueue& rhs) {
    _size = rhs._size;
    priority = rhs.priority;
    Node* temp = rhs._heap;
    this->_heap = copyHelp(this->_heap, temp);
}

JQueue& JQueue::operator=(const JQueue& rhs) {
    Node* temp = rhs._heap;
    if(this->_heap != temp){
        this->~JQueue();
        _size = rhs._size;
        priority = rhs.priority;
        this->_heap = copyHelp(this->_heap, temp);
    }
    return *this;
}

void JQueue::insertJob(const job_t& input) {
    Node* temp = new Node(input);
    _heap = mergeHelp(_heap, temp);
    _size++;
}

job_t JQueue::getNextJob() {
    if(_heap == nullptr){
        throw domain_error("Queue is empty");
    }

    job_struct tempJob(_heap->_job._name, _heap->_job._priority, _heap->_job._user, _heap->_job._group, _heap->_job._proc, _heap->_job._mem, _heap->_job._time);
    Node * tempR = _heap->_right;
    Node * tempL = _heap->_left;
    delete _heap;
    _heap = mergeHelp(tempR, tempL);
    _size--;
    return tempJob;

}

void JQueue::mergeWithQueue(JQueue& rhs) {
    if(priority != rhs.priority){
        throw domain_error("Different priority functions");
    }
    int tempSize = _size + rhs._size;
    _heap = mergeHelp(_heap, rhs._heap);
    _size = tempSize;
    rhs._heap = nullptr;
    rhs._size = 0;
}

void JQueue::clear() {
    _size = 0;
    clearHelp(_heap);
}

int JQueue::numJobs() const {
    return _size;
}

void JQueue::printJobQueue() const {
    preOrder(_heap);
}

prifn_t JQueue::getPriorityFn() const {
    return priority;
}

void JQueue::setPriorityFn(prifn_t priFn) {
    priority = priFn;
    int tempSize = _size;
    JQueue temp(*this);
    this->~JQueue();
    _size = tempSize;
    _heap = new Node(temp.getNextJob());
    while(temp._heap != nullptr){
        _heap = mergeHelp(_heap, new Node(temp.getNextJob()));
    }
}

void JQueue::dump() const {
    dumpHelp(_heap);
    cout << endl;
}

ostream& operator<<(ostream& sout, const job_t& job) {
  sout << "Job: " << job._name << ", pri: " << job._priority
       << ", u: " << job._user << ", g: " << job._group << ", proc: "
       << job._proc << ", mem: " << job._mem << ", time: " << job._time;
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node._job;
  return sout;
}

void JQueue::clearHelp(Node *&move) {
    if( move != NULL )
    {
        clearHelp( move->_left );
        clearHelp( move->_right );
        delete move;
        move = nullptr;
    }
}

void JQueue::dumpHelp(Node *print) const{
    if (print != nullptr) {
        cout << "(";
        dumpHelp(print->_left);
        cout << priority(print->_job);
        dumpHelp(print->_right);
        cout << ")";
    }
}

Node* JQueue::mergeHelp(Node *p1, Node *p2) {
    Node* temp;
    if(p1 == nullptr){
        return p2;
    }
    if(p2 == nullptr){
        return p1;
    }
    if(priority(p1->_job) <= priority(p2->_job)){
        temp = p1;
        p1 = p2;
        p2 = temp;
    }
    temp = p1->_right;
    p1->_right = p1->_left;
    p1->_left = temp;
    p1->_left = mergeHelp(p2, p1->_left);
    return p1;
}

void JQueue::preOrder(Node* move) const{
    if(move != nullptr){
        cout<< "[" << priority(move->_job) << "] ";
        cout<<move->_job<<endl;
        preOrder(move->_left);
        preOrder(move->_right);
    }
}

Node* JQueue::copyHelp(Node *&myRoot, Node *&copyRoot) {
    if(copyRoot == nullptr){
        return NULL;
    }
    job_struct tempJob(copyRoot->_job._name, copyRoot->_job._priority, copyRoot->_job._user, copyRoot->_job._group, copyRoot->_job._proc, copyRoot->_job._mem, copyRoot->_job._time);
    Node* copy = new Node(tempJob);
    copy->_left = copyHelp(myRoot, copyRoot->_left);
    copy->_right = copyHelp(myRoot, copyRoot->_right);
    return copy;
}
