#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
namespace fs = std::filesystem;


void recursive(fs::path const& p, std::vector<std::string>& dic) {
    
	std::error_code ec; //예외사항을 잡아내기위한 클래스
	fs::directory_iterator iter(p, ec);
    
   	//만약 값이 없다면, 함수종료
    	//참고로, std::error_code의 value함수는 예외사항이 발생하면 0이 아닌값을 반환합니다.
	if (ec.value() != 0) return ;

	for (auto& i = iter; i != fs::end(iter); ++i) {// 디렉토리내의 for문 
			
    		//만약 폴더인경우, 해당경로로 함수 재귀적 호출
		if (i->is_directory()){
            dic.push_back(i->path().string());//폴더 경로를 dic에 저장
			recursive(i->path(),dic);
            }
			 
			
		
	}
    
}
int main() {
	std::vector<std::string> dic;
    int count =30;
    std::string *q = new std::string [count];
	fs::path p = fs::current_path();
    recursive(p,dic);
	
	 for (const auto& fileName : dic)
    {
        std::cout << fileName << std::endl;
    }	
}


