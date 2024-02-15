// -*-Mode: Java; tab-width: 4; c-basic-offset: 4;-*-
// vi:set ts=4 sw=4:
//
// AnyElementBetweenExpression.java --
// 
// Copyright (c) 2007, 2010, 2011, 2023 Ricoh Company, Ltd.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 

package jp.co.ricoh.doquedb.hibernate.criterion;

import jp.co.ricoh.doquedb.hibernate.usertype.CollectionType;

import java.sql.Types;

import org.hibernate.Criteria;
import org.hibernate.EntityMode;
import org.hibernate.HibernateException;
import org.hibernate.criterion.CriteriaQuery;
import org.hibernate.criterion.Criterion;
import org.hibernate.criterion.SimpleExpression;
import org.hibernate.engine.spi.SessionFactoryImplementor;
import org.hibernate.engine.spi.TypedValue;
import org.hibernate.type.CustomType;
import org.hibernate.type.Type;
import org.hibernate.usertype.UserType;

/**
 * 任意要素に対する検索条件をあらわすクラスです。
 * 検索対象のカラムが配列型ではない場合には、通常の検索になります。
 */
public class AnyElementBetweenExpression implements Criterion
{
	/** プロパティー名 */
	private final String propertyName;
	/** 検索条件 */
	private final Object lo;
	private final Object hi;

	/**
	 * コンストラクタです。Restrictions からのみ生成可能です。
	 */
	protected AnyElementBetweenExpression(String propertyName,
										  Object lo,
										  Object hi)
	{
		this.propertyName = propertyName;
		this.lo = lo;
		this.hi = hi;
	}

	/**
	 * SQL文を生成します。
	 */
	public String toSqlString(Criteria criteria, CriteriaQuery criteriaQuery)
		throws HibernateException
	{
		// プロパティーに対応するカラムを取り出す
		String[] columns
			= criteriaQuery.getColumnsUsingProjection(criteria, propertyName);
		// プロパティーのタイプを取り出す
		Type type
			= criteriaQuery.getTypeUsingProjection(criteria, propertyName);
		// SessionFactoryを得る
		SessionFactoryImplementor factory = criteriaQuery.getFactory();
		// SQL型を取り出す(この値はUserType.sqlTypes)
		int[] sqlTypes = type.sqlTypes(factory);

		// SQL文を格納するバッファ
		StringBuilder buf = new StringBuilder();

		// カラムが複数あったら、and で結合させるので、括弧を加える
		if (columns.length > 1) buf.append('(');
		for (int i = 0; i < columns.length; ++i)
		{
			buf.append(columns[i]);
			if (sqlTypes[i] == Types.ARRAY)
			{
				// 配列型なので、任意要素の検索になる
				buf.append("[]");
			}
			buf.append(" between ? and ?");
			if (i < columns.length - 1)
				buf.append(" and ");
		}
		if (columns.length > 1) buf.append(')');
		return buf.toString();
	}

	/**
	 * プレースホルダー '?' に対応するオブジェクトを返します。
	 */
	public TypedValue[] getTypedValues(Criteria criteria,
									   CriteriaQuery criteriaQuery)
		throws HibernateException
	{
		Type type = criteriaQuery.getType(criteria, propertyName);
		if (!(type instanceof CustomType))
		{
			throw new HibernateException("unsupported type: " + type);
		}

		CustomType ct = (CustomType)type;
		UserType ut = ct.getUserType();
		if (!(ut instanceof CollectionType))
		{
			throw new HibernateException("unsupported user type: " + ut);
		}

		CollectionType col = (CollectionType)ut;
		return new TypedValue[] {
			new TypedValue(col.getElementType(), lo, EntityMode.POJO),
			new TypedValue(col.getElementType(), hi, EntityMode.POJO)};
	}

	/**
	 * 文字列表現を取り出します
	 */
	public String toString()
	{
		return propertyName + "[]" + " between " + lo + " and " + hi;
	}

}

//
// Copyright (c) 2007, 2010, 2011, 2023 Ricoh Company, Ltd.
// All rights reserved.
//
