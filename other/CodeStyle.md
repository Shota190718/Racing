# コーディング規約

## とっても大事なこと
・**誰が見ても何をしているかわかるようなコーディングを心がけましょう**

## ソースファイル
・ファイル名はクラス名、名前空間名などと一致させる

## ヘッダファイル
・ファイル名はクラス名、名前空間名などと一致させる<br>
・uing namespaceを使わない<br>
・インクルードをできるだけ行わない<br>
・前方宣言をできるだけ用いる<br>

## 変数共通 Variable
・頭文字小文字
```cpp
int variable;
```
・単語区切りを大文字
```cpp
int nomalVariable;
```
・ポインタ型変数は先頭にp
```cpp
int* pNumber;
```
・静的変数もそれに順ずる　

## ローカル変数 Local Variable
・特になし　　

## グローバル変数 Global Variable
・作るな<br>
・使いたければ名前空間で囲む
```cpp
namespace Unichi {

	int UnchiKong;
}　　
```
## 定数共通 Constant
・全文字大文字
```cpp
const int NUMBER = 0;　
```
・単語区切りをアンダーバー
```cpp
const int ARRAY_AMOUNT = 10;　　
```
## ローカル定数 Local Constant
・特になし　　

## グローバル定数 Global Constant
・非推奨　　

## 関数共通 Function
・頭文字大文字			
```cpp
Function()　　
```
・単語区切り大文字		
```cpp
NormalFunction()　
```
・基本動詞から始める	
```cpp
SpreadUnchi()　
```
・開き波かっこは関数宣言の最後の行に書く　<br>
・関数宣言後は一行開ける　　
```cpp
Function() {

	/*  何らかの処理　*/
}
```
## グローバル関数 Global Function
・作るな　　<br>
・使いたければ名前空間で囲む　　
```cpp
namespace Unchi {

	Function();
}
```
## 仮引数 Parameter
・命名は変数共通と同じ　<br>
・基本型以外の型には参照(&)を用いる
```cpp
Function(string& name)　
```
・基本型以外の型でデータの書き換えを行わない場合constをつける　<br>
　この時定数の命名規則にのっとる必要はない　　
 ```cpp
Function(const string& fileName)
```
## 構造体、共用体 Struct, Union
・構造体、共用体名は頭文字大文字　　<br>
・メンバは変数共通に順ずる　　<br>
```cpp
Struct MyStruct {
	int x;
	int y;
};
```
## 列挙型 Enum
・列挙型名は全文字大文字、文字区切りをアンダーバー　　<br>
・メンバも上記と同様　　<br>
・メンバの最後には〇〇_MAXをつける　　
```cpp
Enum MY_ENUM {
	ENUM_ONE,
	ENUM_TWO,
	ENUM_MAX
};
```
## 名前空間 Namespace
・頭文字大文字　　<br>
・単語区切り大文字　　<br>
・変数宣言はヘッダファイルで行わない　　<br>
・変数を外部呼出しする必要な場合はexternを用いる　　<br>
・グローバルな変数、関数を包む　　

## クラス Class
・基本1クラス1ヘッダ1ソース　　<br>
・private修飾子は明示的に記述する　　<br>
・記述順は変数、コンストラクタ、デストラクタ、関数、オペレータ　　<br>
・アクセス修飾子での記述順は関数はpublic, protected, private、変数は逆になる　　<br>
・private, protectedな変数にはアンダーバーをつける　　<br>
・メンバ変数を書き換えない関数はconstをつける　　<br>
・アクセス関数などの１文の関数はヘッダにインライン関数として記述　　<br>
・継承元のクラスのデストラクタは絶対仮想デストラクタにする　　<br>
・クラス継承で関数のオーバーライドを行う場合overrideをつける　　<br>
・コンストラクタでメンバを初期化する場合以下のように記述　　
```cpp
Construct()
	: publicMember(0)
	, privateMember_(124) {

}
```
・少なくともpublicなメンバにはコメントを記述する　　<br>
//// MyClass.h ////　
```cpp
#include <string>

class MyClass {

private:
	std::string name_;

protected:
	int* pNumber_;

public:
	float x;

public:
	MyClass();
	virtual ~MyClass();

public:
	void SetName(std::string& name) { name_ = name; }

protected:
	bool HasNumber() const { return pNumber_ != nullptr; }

private:
	virtual void Netagire();
};
```
//// MyClass.cpp ////　　
```cpp
#include "MyClass.h"

MyClass::MyClass()
	: x(0.0)
	, pNumber_(nullptr)
	, name_("defalt") {
}

MyClass::~MyClass() {

	if (HasNumber()) delete pNumber_;
}

void MyClass::Netagire() {
}
```
//// MyExtend.h ////　　
```cpp
#include "MyClass.h"
	
class MyExtend : public MyClass {

	virtual void Netagire() override {}
};
```
## if文
・ブロックの開きはifと同じ行に書く<br>
・if,elseの後の処理が1文の場合同一行に書く<br>
・else,else ifは改行してから記述<br>
```cpp
if(bool) {

	//何らかの処理
}
else {

	//何らかの処理
}

if(bool) return;
```
## switch文
・ブロックの開きとswitchは同じ行に書く<br>
・caseの中が複数の文で構成されていても{}でかこう必要はない<br>
・caseの中が長い文や複数の文で構成されていている場合は改行してもよい<br>
・caseの値はできるだけenumの値を用いる<br>
・エラー対策のためdefaultは必ずつける
```cpp
switch(value) {

case VALUE_ONE:	func();	break;
case VALUE_TWO:
	func();
	func0();
	break;
default:	break;
}
```
## while文
・ブロックの開きとwhileは同じ行に書く<br>
・無限ループはwhile(true)で統一<br>
```cpp
while(bool) {

	//なんらかの処理	
}
```
## do文
・ブロックの開きとdoは同じ行に書く<br>
・ブロックの閉じとwhileは同じ行に書く<br>
```cpp
do {

	//何らかの処理
} whille(bool);
```
## for文
・ブロックの開きとforは同じ行に書く<br>
・内部の変数はどの範囲を回したいかわかりやすい変数名にする<br>
・多重で間に文を挟まない場合for同士の間に空行を用いない<br>
```cpp
for (int i = 0; i < 10; ++i) {
	
	//何らかの処理
}
for (int x = 0; x < 5; ++x) {
	for (int y = 0; y < 5; ++y) {
	
		//何らかの処理
	}
}
```
## goto文
・知らない子ですね<br>
