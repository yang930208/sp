void DOWHILE(){ <br/>
  // 宣告迴圈開始和結束的標籤 <br/>
  int whileBegin = nextLabel(); <br/>
  int whileEnd = nextLabel(); <br/>
  //跳過do <br/>
  skip("do"); <br/>
  //產生迴圈開始的標籤 <br/>
  emit("(L%d)\n", whileBegin); <br/>
  // 處理迴圈內的陳述 <br/>
  STMT(); <br/>
  //跳過while <br/>
  skip("while"); <br/>
  //跳過左括弧 <br/>
  skip("("); <br/>
  // 處理迴圈的條件表達式，並將結果存儲在變數 e 中 <br/>
  int e = E(); <br/>
  // 產生條件判斷的程式碼，若條件不滿足則跳轉到迴圈開始標籤 <br/>
  emit("if T%d goto L%d\n", e, whileBegin); <br/>
  //跳過右括弧 <br/>
  skip(")"); <br/>
  //跳過分號 <br/>
  skip(";"); <br/>
} <br/>