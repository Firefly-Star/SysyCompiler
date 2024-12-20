### 目前可以识别的产生式:
    产生式                                                           抽象语法树结点
    Root          ::= CompUnit                                      (RootAST)
    CompUnit      ::= [CompUnit] ConstDecl                          (CompUnitAST2)
                    | [CompUnit] FuncDef                            (CompUnitAST1)
                    | [CompUnit] FDef_VDecl                         (CompUnitAST3)

    FDef_VDecl    ::= FVType IDENT FDef_VDeclSuffix                 (FDef_VDeclAST)
    FDef_VDeclSuffix
                  ::= [DimenConstExp] ["=" InitVal] ["," VarDefs] ";" (FDef_VDeclSuffixAST1)
                    | "(" [FuncFParams] ")" Block                     (FDef_VDeclAST2)

    FVType        ::= "int" | "float"

    Decl          ::= ConstDecl                                     (DeclAST1)
                    | VarDecl                                       (DeclAST2)
    ConstDecl     ::= "const" BType ConstDefs ";"                   (ConstDeclAST)
    BType         ::= "int" |"float"                                (BTypeAST)
    ConstDefs     ::= ConstDef ["," ConstDefs]                      (ConstDefsAST)
    ConstDef      ::= IDENT [DimenConstExp] "=" ConstInitVal        (ConstDefAST)
    DimenConstExp ::= "[" ConstExp "]" [DimenConstExp]              (DimenConstExpAST)
    ConstInitVal  ::= ConstExp                                      (ConstInitValAST1)
                    | "{" [ConstInitVals] "}"                       (ConstInitValAST2)
    ConstInitVals ::= ConstInitVal ["," ConstInitVals]              (ConstInitValsAST)
    
    VarDecl       ::= BType VarDefs ";"                             (VarDeclAST)
    VarDefs       ::= VarDef ["," VarDefs]                          (VarDefsAST)
    VarDef        ::= IDENT [DimenConstExp]                         (VarDefAST1)
                    | IDENT [DimenConstExp] "=" InitVal             (VarDefAST2)
    InitVal       ::= Exp;                                          (InitValAST1)
                    | "{" [InitVals] "}"                            (InitValAST2)
    InitVals      ::= InitVal ["," InitVals]                        (InitValsAST)

    FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block    (FuncDefAST)
    FuncType      ::= "void"                                        (FuncTypeAST)
    FuncFParams   ::= FuncFParam ["," FuncFParams]                  (FuncFParamsAST)
    FuncFParam ::= BType IDENT ["[" "]" [DimenConstExp]]            (FuncFParamAST)

    Block         ::= "{" [BlockItems] "}"                          (BlockAST)
    BlockItems    ::= BlockItem [BlockItems]                        (BlockItemsAST)
    BlockItem     ::= Decl                                          (BlockItemAST1) 
                    | Stmt                                          (BlockItemAST2)
    Stmt          ::= LVal "=" Exp ";"                              (StmtAST2)
                    | [Exp] ";"                                     (StmtAST3)
                    | Block                                         (StmtAST4)
                    | "if" "(" Exp ")" Stmt ["else" Stmt]           (StmtAST5)
                    | "while" "(" Exp ")" Stmt                      (StmtAST6)
                    | "break" ";"                                   (StmtAST7)
                    | "continue" ";"                                (StmtAST8)
                    | "return" [Exp] ";"                            (StmtAST1)

    Exp           ::= LOrExp                                        (ExpAST)
    LVal          ::= IDENT [DimenExp]                              (LValAST)
    DimenExp      ::= "[" Exp "]" [DimenExp]                        (DimenExpAST)
    PrimaryExp    ::= "(" Exp ")"                                   (PrimaryExpAST1)
                    | LVal                                          (PrimaryExpAST3)
                    | Number                                        (PrimaryExpAST2)
    Number        ::= INT_CONST;
    UnaryExp      ::= PrimaryExp                                    (UnaryExpAST1)
                    | IDENT "(" [FuncRParams] ")"                   (UnaryExpAST3)
                    | UnaryOp UnaryExp                              (UnaryExpAST2)
    UnaryOp       ::= "+" | "-" | "!";
    FuncRParams   ::= Exps;                                         (FuncRParamsAST)
    Exps          ::= Exp ["," Exps]                                (ExpsAST)
    MulExp        ::= UnaryExp                                      (MulExpAST1)
                    | MulExp ("*" | "/" | "%") UnaryExp             (MulExpAST2)
    AddExp        ::= MulExp                                        (AddExpAST1)
                    | AddExp ("+" | "-") MulExp                     (AddExpAST2)
    RelExp        ::= AddExp                                        (RelExpAST1) 
                    | RelExp ("<" | ">" | "<=" | ">=") AddExp       (RelExpAST2)
    EqExp         ::= RelExp                                        (EqExpAST1) 
                    | EqExp ("==" | "!=") RelExp                    (EqExpAST2)
    LAndExp       ::= EqExp                                         (LAndExpAST1) 
                    | LAndExp "&&" EqExp                            (LAndExpAST2)
    LOrExp        ::= LAndExp                                       (LOrExpAST1)
                    | LOrExp "||" LAndExp                           (LOrExpAST2)
    ConstExp      ::= Exp;                                          (ConstExpAST)
