
/*****************************************************************************
*  queue.h                                                                   *
*  Copyright (C) 2019.10.30 TriAlley  lg139@139.com                          *
*  @brief    ������е�ʵ��                                                   *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
/*queue
public:
    enum queue_err { queue_empty };  //�����Ĵ���
private:
    struct node;					//�������
    node* _head;					//ͷ���ָ��
    node* _end;						//β���ָ�룬ָ��nullptr
    int _length;					//Ԫ�ظ���
public:
    queue ();						//���캯��
    ~queue ();						//��������
    void push ( const T& in );		//�����
    T front ();						//�����Ԫ��
    void pop ();					//������Ԫ��
    bool isempty ()const;			//�Ƿ�Ϊ��
    int size ()const;				//��ȡԪ�ظ���
*/
template<typename T>
class queue {
public:
    enum queue_err { queue_empty };
private:
    typedef struct node {
        T data;
        node* next;
        node () { next = nullptr; }
    }node;
    node* _head;
    node* _end;
    int _length;
public:
    queue () {
        _head = new node;
        _end = _head;
        _length = 0;
    }
    ~queue () {
        until (_head->next == nullptr) {
            node* temp = _head;
            _head = _head->next;
            delete temp;
        }
        delete _head;
    }

    void push (const T& in) {
        _length++;
        node* n_end = new node;
        n_end->data = in;
        n_end->next = nullptr;

        _end->next = n_end;
        _end = n_end;
    }
    T front () {
        if (isempty ()) {
            throw queue_empty;
        }
        return _head->next->data;
    }
    void pop () {
        if (isempty ()) {
            throw queue_empty;
        }
        node* n_head = _head->next;
        delete _head;

        _head = n_head;

        _length--;
        return;
    }
    bool isempty ()const { return _head == _end; }
    int size ()const { return _length; }
};