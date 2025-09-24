# Error Case
## 1. duplicate symbol '_main' 에러
* 같은 폴더 내에 main함수를 가지는 cpp 파일이 여러개 있는 경우 에러가 나는 것이다. 
* 빌드 과정에서 프로그램이 시작되는 지점이 main 인데 이것이 여러 파일에서 찾을 수 있어 나는 에러로 보인다. 