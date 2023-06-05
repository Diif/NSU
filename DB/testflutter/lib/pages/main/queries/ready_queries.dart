import 'p_query.dart';

List<PQuery> queries = [];

void fillQueries(){
  queries.add(const PQuery(
      """Получить сведения о покупателях, которые не пришли забрать свой заказ в назначенное им
время и общее их число.""",
      """SELECT DISTINCT first_name, last_name,middle_name, phone , ROW_NUMBER() OVER() AS num FROM 
(
	SELECT DISTINCT client_id FROM client_orders
		WHERE stage IN
			(
			SELECT id FROM client_order_stages
			WHERE stage_name='готово' OR stage_name='выдано'
			)
		AND (((receive_time IS NOT NULL) AND (CAST(receive_time AS DATE) > CAST(ready_time AS DATE))) OR (receive_time IS NULL AND CAST(ready_time AS DATE) < CAST(CURRENT_DATE AS DATE)))
)
AS SQ INNER JOIN clients ON (clients.id = SQ.client_id)
ORDER BY num DESC"""
      , ["Имя", "Фамилия", "Отчество", "Телефон", "Количество клиентов"], [],[]));

  queries.add(const PQuery(
      """Получить перечень и общее число покупателей, которые ждут прибытия на склад нужных им медикаментов в целом""",
      """SELECT first_name, last_name, middle_name, phone, ROW_NUMBER() OVER() AS num FROM 
(
	SELECT first_name, last_name, middle_name, phone FROM clients
		WHERE id IN
			(
			SELECT client_id FROM client_orders
			WHERE stage=(SELECT id FROM client_order_stages WHERE stage_name='ожидание')
			)
)SQ1
ORDER BY num DESC"""
      , ["Имя", "Фамилия", "Отчество", "Телефон", "Количество клиентов"], [],[]));

  queries.add(const PQuery(
      """Получить перечень и общее число покупателей, которые ждут прибытия на склад нужных им медикаментов по указанной категории медикаментов""",
      """SELECT first_name, last_name, middle_name, phone, ROW_NUMBER() OVER() AS num FROM
(
	SELECT DISTINCT client_id FROM
	(
		SELECT client_order_id FROM
		(
			SELECT substance_id, client_order_id FROM client_order_sub_rel
			WHERE count!=reserved AND is_final_product=true
		) AS SQ1 
		INNER JOIN substances ON (substances.id = substance_id)
		WHERE substances.category_id=(SELECT id FROM categories WHERE name=@category_name)
		GROUP BY client_order_id
	) AS SQ2
	INNER JOIN client_orders ON (client_order_id = client_orders.id)
	WHERE stage=(SELECT id FROM client_order_stages WHERE stage_name='ожидание')
) AS SQ3
INNER JOIN clients ON (clients.id = SQ3.client_id)
ORDER BY num DESC"""
      , ["Имя", "Фамилия", "Отчество", "Телефон", "Количество клиентов"],["category_name"], ["Название категории"]));

  queries.add(const PQuery(
      """Получить перечень десяти наиболее часто используемых медикаментов в целом""",
      """SELECT name, total_count FROM
(
	SELECT *, RANK() OVER(ORDER BY total_count DESC)FROM
	(
	SELECT substances.id, substances.name, SUM(client_order_sub_rel.count) total_count FROM substances
	INNER JOIN client_order_sub_rel 
	ON (substances.id = client_order_sub_rel.substance_id)
	GROUP BY substances.id, substances.name
	) SQ
) SQ2
WHERE SQ2.rank <= 10"""
      , ["Наименование", "Количество"],[], []));

  queries.add(const PQuery(
      """Получить перечень десяти наиболее часто используемых медикаментов в целом""",
      """SELECT name, total_count FROM
(
	SELECT *, RANK() OVER(ORDER BY total_count DESC)FROM
	(
	SELECT substances.id, substances.name, SUM(client_order_sub_rel.count) total_count FROM substances
	INNER JOIN client_order_sub_rel 
	ON (substances.id = client_order_sub_rel.substance_id)
	GROUP BY substances.id, substances.name
	) SQ
) SQ2
WHERE SQ2.rank <= 10"""
      , ["Наименование", "Количество"],[], []));

  queries.add(const PQuery(
      """Получить перечень десяти наиболее часто используемых медикаментов в указанной категории медикаментов""",
      """SELECT name, total_count FROM
(
	SELECT *, RANK() OVER(ORDER BY total_count DESC)FROM
	(
	SELECT substances.id, substances.name, SUM(client_order_sub_rel.count) total_count FROM substances
	INNER JOIN client_order_sub_rel 
	ON (substances.id = client_order_sub_rel.substance_id)
	WHERE category_id=(SELECT id FROM categories WHERE name=@category_name)
	GROUP BY substances.id, substances.name
	) SQ
) SQ2
WHERE SQ2.rank <= 10"""
      , ["Наименование", "Количество"],['category_name'], ["Название категории"]));

  queries.add(const PQuery(
      """Получить какой объем указанных веществ использован за указанный период""",
      """SELECT substances.name, COUNT(client_order_sub_rel.count) AS total_count FROM
(
	SELECT id FROM client_orders
	WHERE order_time BETWEEN @start AND @end
) AS SQ1
INNER JOIN client_order_sub_rel ON (SQ1.id = client_order_sub_rel.client_order_id)
INNER JOIN substances ON (client_order_sub_rel.substance_id = substances.id)
WHERE name IN (@sub)

GROUP BY substances.id, substances.name
ORDER BY total_count DESC
LIMIT 10
"""
      , ["Наименование", "Количество"],['start', 'end', 'sub'],['2023-01-26 10:23:40', "2023-02-28 10:23:40", "наименование"]));

  queries.add(const PQuery(
      """Получить перечень и общее число покупателей, заказывавших определенное лекарство  за данный период""",
      """SELECT first_name, last_name, middle_name, phone, ROW_NUMBER() OVER() num FROM clients
WHERE id IN
(
	SELECT client_id FROM client_orders
	WHERE id IN
	(
		SELECT client_order_id FROM client_order_sub_rel
		WHERE substance_id=
		(
			SELECT id FROM substances
			WHERE name=@sub
		)
	)
	AND order_time BETWEEN @start AND @end
)
ORDER BY num DESC
"""
      , ["Имя", "Фамилия", "Отчество", "Телефон", "Количество клиентов"],['start', 'end', 'sub'],['2023-01-26 10:23:40', "2023-02-28", "наименование"]));

  queries.add(const PQuery(
      """Получить перечень и общее число покупателей, заказывавших определенные типы лекарств за данный период""",
      """SELECT first_name, last_name, middle_name, phone, ROW_NUMBER() OVER() num FROM clients
WHERE id IN
(
	SELECT client_id FROM client_orders
	WHERE id IN
	(
		SELECT client_order_id FROM client_order_sub_rel
		WHERE substance_id IN
		(
			SELECT id FROM substances
			WHERE category_id=
			(
				SELECT id FROM categories
				WHERE name=@category_name
			)
		)
	)
	AND order_time BETWEEN @start AND @end
)
ORDER BY num DESC
"""
      , ["Имя", "Фамилия", "Отчество", "Телефон", "Количество клиентов"],['start', 'end', 'category_name'],['2023-01-26 10:23:40', "2023-02-28", "категория"]));

  queries.add(const PQuery(
      """Получить перечень и типы лекарств, достигших своей критической нормы или закончившихся""",
      """
SELECT name, crit_count, count FROM substances
WHERE count<=crit_count
"""
      , ["Наименование", "Критическое количество", "Количество"],[],[]));

  queries.add(const PQuery(
      """Получить перечень лекарств с минимальным запасом на складе в целом""",
      """
SELECT name, crit_count, count FROM substances
WHERE count <=
	(
	SELECT MIN(count) FROM substances
	)
"""
      , ["Наименование", "Критическое количество", "Количество"],[],[]));

  queries.add(const PQuery(
      """Получить перечень лекарств с минимальным запасом на складе по указанной категории медикаментов""",
      """
SELECT name, crit_count, count FROM substances
WHERE count <=
	(
	SELECT MIN(count) FROM substances
		WHERE category_id=
		(
			SELECT id FROM categories
			WHERE name=@category_name
		)
	)
"""
      , ["Наименование", "Критическое количество", "Количество"],["category_name"],["Название категории"]));

}
