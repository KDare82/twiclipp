/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include "StatusData.h"
#include "tinyxml/tinyxml.h"

StatusData::StatusData(const TiXmlNode & xmlElement)
  : screenName(xmlElement.FirstChild("user")->FirstChild("screen_name")->ToElement()->GetText()),
    fullName(xmlElement.FirstChild("user")->FirstChild("name")->ToElement()->GetText()),
    text(xmlElement.FirstChild("text")->ToElement()->GetText()),
    creationDate(xmlElement.FirstChild("created_at")->ToElement()->GetText())
{
}

StatusData::~StatusData()
{
}
