class Node:
    def __init__(self, data, next: "Node" = None, prev: "Node" = None, origin: "List" = None) -> None:
        self.data = data
        self.next = next
        self.prev = prev
        self.origin = origin

class List:
    def __init__(self) -> None:
        self.size = int(0)

        self.head = Node(0, None, None, self)
        self.tail = Node(0, None, None, self)

        self.head.next = self.tail
        self.tail.prev = self.head
    
    def is_empty(self) -> bool:
        return self.size == 0
    
    def is_in_list(self, node: Node) -> bool:
        return node.origin == self
    
    def push_back(self, data) -> None:
        n = Node(data, self.tail, self.tail.prev, self)
        
        self.tail.prev.next = n
        self.tail.prev = n
        self.size += 1
    
    def push_front(self, data) -> None:
        n = Node(data, self.head.next, self.head, self)
        
        self.head.next.prev = n
        self.head.next = n
        self.size += 1

    def pop_back(self) -> None:
        if self.size == 0:
            raise IndexError("Cannot pop from an empty List")
        
        data = self.tail.prev.data

        self.tail.prev.prev.next = self.tail
        self.tail.prev = self.tail.prev.prev
        self.size -= 1

        return data
    
    def pop_front(self) -> None:
        if self.size == 0:
            raise IndexError("Cannot pop from an empty List")
        
        data = self.head.next.data

        self.head.next.next.prev = self.head
        self.head.next = self.head.next.next
        self.size -= 1
    
        return data

    def pop_node(self, node: Node) -> None:
        if node == None:
            raise ValueError("A node must be provided")

        if not self.is_in_list(node):
            raise RuntimeError("The node does not belong to the List")
        
        if node == self.head or node == self.tail:
            raise IndexError("The provided node is out of range")
        
        node.next.prev, node.prev.next = node.prev, node.next
        self.size -= 1

    def clear(self) -> None:
        while self.size != 0:
            self.pop_back()

    def __iter__(self):
        curr = self.head.next

        while curr != self.tail:
            yield curr.data
            curr = curr.next
    
    def __reversed__(self):
        curr = self.tail.prev

        while curr != self.head:
            yield curr.data
            curr = curr.prev
