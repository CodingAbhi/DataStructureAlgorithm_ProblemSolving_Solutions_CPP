class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def lvl_order_traversal(root):
    if not root:
        return []

    result = []
    queue = [root]

    while queue:
        level_vals = []
        level_size = len(queue)

        for _ in range(level_size):
            node = queue.pop(0)
            level_vals.append(node.val)

            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

        result.append(level_vals)

    return result


def tree_list(nodes, index=0):
    if index < len(nodes):
        if nodes[index] is None:
            return None
        node = TreeNode(nodes[index])
        node.left = tree_list(nodes, 2 * index + 1)
        node.right = tree_list(nodes, 2 * index + 2)
        return node
    return None


# Taking binary tree input from the user
input_str = input(
    "Enter the binary tree values: ")
print(end='\n')
tree_values = input_str.split()
tree_values = [None if val == 'None' else int(val) for val in tree_values]
root = tree_list(tree_values)

# Getting the level order traversal
output = lvl_order_traversal(root)
print("list format :", output)
