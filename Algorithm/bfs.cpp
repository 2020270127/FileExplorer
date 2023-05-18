#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
namespace fs = std::filesystem;
using namespace std;
void recursive(fs::path const& p, std::vector<std::string>& dic,queue<string>& que) {
    
	std::error_code ec; //예외사항을 잡아내기위한 클래스
	fs::directory_iterator iter(p, ec);
    
   	//만약 값이 없다면, 함수종료
    	//참고로, std::error_code의 value함수는 예외사항이 발생하면 0이 아닌 값을 반환합니다.
	if (ec.value() != 0) return ;

	for (auto& i = iter; i != fs::end(iter); ++i) {// 디렉토리내의 for문 
			
    		//만약 폴더인경우, 해당경로로 함수 재귀적 호출
		if (i->is_directory()){
            que.push(i->path().string());
			dic.push_back(i->path().string());
            }
			 
	
	}
	
	 if (que.empty())
	{
		return;
	}	
	else if(!que.empty()){
		string temp = que.front();
		que.pop();
		recursive(temp,dic,que);
	}
	
	
    

}

int main() {
	std::vector<std::string> dic;
    queue<string> que;
    
	fs::path p ="/Users/";
    recursive(p,dic,que);
	
	 for (const auto& fileName : dic)
    {
        std::cout << fileName << std::endl;
    }	
}


