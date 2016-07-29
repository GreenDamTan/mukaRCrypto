#include "IceKey.H"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Security::Cryptography;


int main(array<System::String ^> ^args)
{
	Console::WriteLine(L"1. ���� 2. ����");
	auto readkey = Console::ReadKey(true);
	auto ice = new IceKey(0);
	auto dir = gcnew DirectoryInfo(L"./");
	array<FileInfo ^> ^ files;
	bool flag = false;
	if (readkey.KeyChar == L'1') {
		files = dir->GetFiles(L"*.png");
		flag = true;
	}
	else if (readkey.KeyChar == L'2') {
		files = dir->GetFiles(L"*.mukaR");
	}
	else {
		return 0;
	}
	for each (auto file in files)
	{
		if (flag)
			Console::WriteLine(L"���ܣ�" + file->Name);
		else
			Console::WriteLine(L"���ܣ�" + file->Name);
		auto filename = file->Name->Replace(file->Extension, L"");
		auto input = File::ReadAllBytes(file->FullName);
		auto length = input->Length;
		pin_ptr<unsigned char> inputp = &input[0];
		auto output = gcnew array<unsigned char>(length);
		pin_ptr<unsigned char> outputp = &output[0];
		auto md5input = Encoding::UTF8->GetBytes(L"Zhanjian" + filename);
		auto md5 = gcnew MD5CryptoServiceProvider();
		auto md5output = md5->ComputeHash(md5input);
		auto keytext = BitConverter::ToString(md5output)->Replace("-", "")->ToLower();
		auto key = Encoding::UTF8->GetBytes(keytext);
		pin_ptr<unsigned char> keyp = &key[0];
		ice->set(keyp);
		if (flag) {
			for (int i = 0; i < length; i = i + 8) {
				ice->encrypt(&inputp[i], &outputp[i]);
			}
			File::WriteAllBytes(filename + L".mukaR", output);
		}
		else {
			for (int i = 0; i < length; i = i + 8) {
				ice->decrypt(&inputp[i], &outputp[i]);
			}
			File::WriteAllBytes(filename + L".png", output);
		}
	}
	Console::WriteLine(L"���в�������ɣ�");
	Console::Read();
	return 0;
}
