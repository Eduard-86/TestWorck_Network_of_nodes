# TestWorck_Network_of_nodes

Создайте сеть абстрактных узлов, и метод ее обновления, работающий по следующему принципу:
- Каждый узел сети может выполнить одно из следующих действий:
  - Узел сети может создать событие несущее некоторые данные, в рамках тестового задания: случайное число
  - Узел сети может подписаться на события любого соседа любого своего соседа, кроме самого себя
  - Узел сети может отписаться от любого своего соседа
  - Узел может создать новый узел и подписаться на него, при этом новый созданный узел не участвует в текущем обновлении
  - Узел не выполняет никаких действий
- При подписке узел назначает один из следующих обработчиков события:
  - Вывод в консоль "имя_отправителя -> имя_получателя: S = сумма_всех_чисел_полученных_от_этого_отправителя"
  - Вывод в консоль "имя_отправителя -> имя_получателя: N = число_событий_полученных_от_этого_отправителя"
- Если узел лишается всех соседей, то он уничтожается в конце процедуры обновления сети
Узлы считаются соседями, если один их них подписан на события другого.
В случае невозможности выполнения выбранного узлом действия, попыток выполнить другое действие не осуществляется.

Обновление узлов сети должно происходить синхронно, то есть изменения, созданные в процессе обновления уже обработанными узлами, не должны учитываться узлами которые еще не обработаны.
Вероятность каждого события задается вручную при запуске программы.
Стартовая сеть создается при запуске случайным образом с произвольными параметрами, которые вы можете по желанию задавать с клавиатуры либо задавать случайно.
Программа должна продолжать симуляцию до вырождения сети, либо до явной остановки симуляции.
 
	У Ноды должны быть 
		Контейнер Делегатов того кто на тебя подписан "чтобы ты вызвал все методы всех кто на тебя подписан"
		Контейнер тех на кого ты подписан, чтобы знать кто вызвал твой делегат
		Медов добавления числа и подсчёта №1
		Модов добавления числа и подсчёта №2
		Мотод подписки/отписки на узел соседа соседа 
		
		И ещё какието методы....
		
	У Сети должны быть 
		Контейнер Нод "Надоли"
		Метод пост/преф и основнова тика 
		