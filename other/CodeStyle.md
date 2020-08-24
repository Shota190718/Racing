# コーディング規約

## とっても大事なこと
・誰が見ても何をしているかわかるようなコーディングを心がけましょう

## ソースファイル
・ファイル名はクラス名、名前空間名などと一致させる

## ヘッダファイル
・ファイル名はクラス名、名前空間名などと一致させる　　
・uing namespaceを使わない　　
・インクルードをできるだけ行わない　　
・前方宣言をできるだけ用いる　　

## 変数共通 Variable
・頭文字小文字  int variable;  ・単語区切りを大文字  int nomalVariable;  ・ポインタ型変数は先頭にp  int* pNumber;  ・静的変数もそれに順ずる　　

## ローカル変数 Local Variable
・特になし　　

## グローバル変数 Global Variable
・作るな　　
・使いたければ名前空間で囲む　　
	namespace Unichi {

		int UnchiKong;
	}　　

## 定数共通 Constant
・全文字大文字				const int NUMBER = 0;　　
・単語区切りをアンダーバー	const int ARRAY_AMOUNT = 10;　　

## ローカル定数 Local Constant
・特になし　　

## グローバル定数 Global Constant
・非推奨　　

## 関数共通 Function
・頭文字大文字			Function()　　
・単語区切り大文字		NormalFunction()　　
・基本動詞から始める	SpreadUnchi()　　
・開き波かっこは関数宣言の最後の行に書く　　
・関数宣言後は一行開ける　　
	Function() {

		/*  何らかの処理　*/
	}

## グローバル関数 Global Function
・作るな　　
・使いたければ名前空間で囲む　　
	namespace Unchi {

		Function();
	}

## 仮引数 Parameter
・命名は変数共通と同じ　　
・基本型以外の型には参照(&)を用いる		Function(string& name)　　
・基本型以外の型でデータの書き換えを行わない場合constをつける　　
　この時定数の命名規則にのっとる必要はない　　
	Function(const string& fileName)

## 構造体、共用体 Struct, Union
・構造体、共用体名は頭文字小文字　　
・メンバは変数共通に順ずる　　
	Struct MyStruct {

		int x;
		int y;
	};

## 列挙型 Enum
・列挙型名は全文字大文字、文字区切りをアンダーバー　　
・メンバも上記と同様　　
・メンバの最後には〇〇_MAXをつける　　
	Enum MY_ENUM {
		ENUM_ONE,
		ENUM_TWO,
		ENUM_MAX
	};

## 名前空間 Namespace
・頭文字大文字　　
・単語区切り大文字　　
・変数宣言はヘッダファイルで行わない　　
・変数を外部呼出しする必要な場合はexternを用いる　　
・グローバルな変数、関数を包む　　

## クラス Class
・基本1クラス1ヘッダ1ソース　　
・private修飾子は明示的に記述する　　
・記述順は変数、コンストラクタ、デストラクタ、関数、オペレータ　　
・アクセス修飾子での記述順はpublic, protected, private　　
・private, protectedな変数にはアンダーバーをつける　　
・メンバ変数を書き換えない関数はconstをつける　　
・アクセス関数などの１文の関数はヘッダにインライン関数として記述　　
・継承元のクラスのデストラクタは絶対仮想デストラクタにする　　
・クラス継承で関数のオーバーライドを行う場合overrideをつける　　
・コンストラクタでメンバを初期化する場合以下のように記述　　
	Construct()
		: publicMember(0)
		, privateMember_(124) {

	}
・少なくともpublicなメンバにはコメントを記述する　　
//// MyClass.h ////　　
#include <string>

	class MyClass {
	
	public:
		float x;

	protected:
		int* pNumber_;

	private:
		std::string name_;

	public:
		MyClass();
		virtual ~MyClass();

	public:
		void SetName(std::string& name) { name_ = name; }

	protected:
		bool HasNumber() const { return pNumber_ != nullptr; }

	private:
		virtual void Netagire();
	}

//// MyClass.cpp ////　　
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

//// MyExtend.h ////　　
	#include "MyClass.h"

	class MyExtend : public MyClass {
	
		virtual void Netagire() override {}
	}
