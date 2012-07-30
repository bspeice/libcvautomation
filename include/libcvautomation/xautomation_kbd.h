/*
 *  
 *  Copyright (c) 2002 Steve Slaven, All Rights Reserved.
 *  
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 *  
*/

#define NUM_KEY_MODIFIERS 3
/* ISO_Level3_Shift = AltGr */
char *key_modifiers[] = { NULL, "Mode_switch", "ISO_Level3_Shift" };
char *shift_key = "Shift_L";

#define MAX_KEYSYM 65536
/* this maps what keysyms need a modifier pushed */
int keysym_to_modifier_map[ MAX_KEYSYM ];
KeyCode keysym_to_keycode_map[ MAX_KEYSYM ];
