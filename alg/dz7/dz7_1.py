from collections import deque

class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right


def build_tree(values):
    if not values or values[0] == '0':
        return None
        
    root = Node(int(values[0]))
    queue = deque([root])
    index = 1
    
    while queue and index < len(values):
        current = queue.popleft()
        
        if index < len(values):
            left_val = values[index]
            if left_val != '0':
                current.left = Node(int(left_val))
                queue.append(current.left)
            index += 1
            
        if index < len(values):
            right_val = values[index]
            if right_val != '0':
                current.right = Node(int(right_val))
                queue.append(current.right)
            index += 1
            
    return root


def is_symmetric(root):
    if root is None:
        return True
    return is_mirror(root.left, root.right)


def is_mirror(t1, t2):
    if t1 is None and t2 is None:
        return True
    if t1 is None or t2 is None:
        return False
    
    return (t1.value == t2.value and 
            is_mirror(t1.left, t2.right) and 
            is_mirror(t1.right, t2.left))


def main():
    print("Введите элементы дерева через пробел (если элемента нет - 0):")
    user_input = input().split()
    
    root = build_tree(user_input)
    
    result = is_symmetric(root)
    print("Результат проверки на симметричность:", result)


if __name__ == "__main__":
    main()