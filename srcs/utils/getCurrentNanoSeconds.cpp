/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getCurrentNanoSeconds.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:50:12 by jguyet            #+#    #+#             */
/*   Updated: 2018/01/31 13:50:14 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>

long						getCurrentNanoSeconds( void )
{
	auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);

    auto value = now_ms.time_since_epoch();
    return (value.count());
}
