/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

PTreeNode *_dxfMakeArg(int);
PTreeNode *_dxfMakeFunCall(char *, PTreeNode *);
PTreeNode *_dxfMakeList(int op, PTreeNode *);
PTreeNode *_dxfMakeBinOp(int, PTreeNode *, PTreeNode *);
PTreeNode *_dxfMakeUnOp(int, PTreeNode *);
PTreeNode *_dxfMakeConditional(PTreeNode *, PTreeNode *, PTreeNode *);
PTreeNode *_dxfMakeInput(int);
PTreeNode *_dxfMakeAssignment(char *, PTreeNode*);
PTreeNode *_dxfMakeVariable(char *);

extern int _dxdparseError;

