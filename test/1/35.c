#if 0
재귀 호출은 이름이 같은 함수를 새롭게 호출하는 것이다.
함수 안에서 함수를 호출하는 구조가 결코 아니다.
Call Stack 을 별도로 생성하게 되며
기계어 분석에서 살펴봤던 스택 프레임을 생성하게 된다.
결국 재귀호출이 빈번하게 일어나면
스택 프레임의 생성과 해제가 빈번하게 발생하므로 성능이 떨어지게 된다.
반면 프로그램의 작성은 쉬워지기 때문에 양날검이다.
#endif
