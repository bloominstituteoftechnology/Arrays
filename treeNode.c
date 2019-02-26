struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
}

int** zig(struct TreeNode * root, int** columnSizes, int* returnSize) {
  int *ret = malloc(sizeof(returnSize) * sizeof(columnSizes));

  // Outer array
  for (int i = 0; i < *returnSize; i++) {

    // Root is always at ret[0][0]
    if (i == 0) {   
      ret[i][0] = *root->val;

    // For each additional level of the Tree struct
    } else {

      // Inner array is the length of the column
      for (j = 0; j < **columnSizes; j+=2) {  // binary has 2 children per node 

        // Odd levels are written right to left
        if (i % 2) {
        ret[i][j] = *root->right->val;
        ret[i][j+1] = *root->left->val;
        }

        // Even levels are left right
        else {
          ret[i][j] = *root->left->val;
          ret[i][j+1] = *root->right->val;
        }
      }
    }
  }
}

# #Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

// class Solution:
//     def zigzagLevelOrder(self, root):
//         """
//         :type root: TreeNode
//         :rtype: List[List[int]]
//         """
//         #base case if tree empty
//         if not root:
//             return []
        
//         #define tree and append root to current_level
//         tree = []
//         current_level = [root]
//         #assume first pass is left to right
//         left_right = True
//         #break loop once current level is empty
//         while current_level:
//             levels = []
//             next_level = []
//             #iterate through current
//             for i in current_level:
//                 # append the values to levels
//                 levels.append(i.val)
//                 if i.left:
//                     #append the children to next level, left first
//                     next_level.append(i.left)
//                 if i.right:
//                     next_level.append(i.right)
//             if left_right:
//                 #if left_right first append levels as is
//                 tree.append(levels)
//                 left_right = not left_right 
//             else:
//                 #if not append in reverse
//                 tree.append(levels[::-1])
//                 left_right = not left_right
//             #set to the next_level to continue loop. breaks once all children are counted.
//             current_level = next_level
//         return tree