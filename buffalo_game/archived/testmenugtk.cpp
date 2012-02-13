/* test-ui-mananager.c : Simple tutorial for GtkUIManager
 * Copyright (C) 2005 Ryan McDougall.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>


/* Create callbacks that implement our Actions */
static void     
lookup_character_action ()
{
        g_print ("lookup\n");
}

static void     
clear_character_action ()
{
        g_print ("clear\n");
}

static void     
quit_action ()
{
        gtk_main_quit();
}


/* Create a list of entries which are passed to the Action constructor. 
 * This is a huge convenience over building Actions by hand. */
static GtkActionEntry entries[] = 
{
  { "FileMenuAction", NULL, "_File" },                  /* name, stock id, label */
  { "CharacterMenuAction", NULL, "_Character" },

  
  { "LookupAction", GTK_STOCK_FIND,                     /* name, stock id */
    "_Lookup", "<control>L",                            /* label, accelerator */
    "Look-up the character drawn",                      /* tooltip */ 
    G_CALLBACK (lookup_character_action) },
    
  { "ClearAction", GTK_STOCK_OPEN,
    "_Clear","<control>C",  
    "Clear the drawing area",
    G_CALLBACK (clear_character_action) },
    
  { "QuitAction", GTK_STOCK_QUIT,
    "_Quit", "<control>Q",    
    "Quit",
    G_CALLBACK (quit_action) }
};

static guint n_entries = G_N_ELEMENTS (entries);


/*---------------------------------------------------------------------------*/

int
main (int argc, char** argv)
{
    GtkWidget           *window;                /* The main window */
    GtkWidget           *menu_box;              /* Packing box for the menu and toolbars */
    GtkActionGroup      *action_group;          /* Packing group for our Actions */
    GtkUIManager        *menu_manager;          /* The magic widget! */
    GError              *error;                 /* For reporting exceptions or errors */
    GtkWidget           *menubar;               /* The actual menubar */
    GtkWidget           *toolbar;               /* The actual toolbar */
  
        /* Always the first step is to start up GTK+ itself */
    gtk_init (&argc, &argv);
    
    /* Create our objects */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    menu_box = gtk_vbox_new (FALSE, 0);
    action_group = gtk_action_group_new ("TestActions");
    gtk_action_group_set_translation_domain (action_group, "blah");
    menu_manager = gtk_ui_manager_new ();
    
    /* Pack up our objects:
     * menu_box -> window
     * actions -> action_group
     * action_group -> menu_manager */
    gtk_container_add (GTK_CONTAINER(window), menu_box);
    gtk_action_group_add_actions (action_group, entries, n_entries, NULL);
    gtk_ui_manager_insert_action_group (menu_manager, action_group, 0);
    
    /* Read in the UI from our XML file */
    error = NULL;
    gtk_ui_manager_add_ui_from_file (menu_manager, "test-ui-manager-ui.xml", &error);
    
    if (error)
    {
        g_message ("building menus failed: %s", error->message);
        g_error_free (error);
    }
    
    /* Connect up important signals */
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    
    /* Get the menubar and the toolbar and put them in the vertical packing box */
    menubar = gtk_ui_manager_get_widget (menu_manager, "/MainMenu");
    gtk_box_pack_start (GTK_BOX (menu_box), menubar, FALSE, FALSE, 0);
    toolbar = gtk_ui_manager_get_widget (menu_manager, "/MainToolbar");
    gtk_box_pack_start (GTK_BOX (menu_box), toolbar, FALSE, FALSE, 0);

    /* Make sure that the accelerators work */
    gtk_window_add_accel_group (GTK_WINDOW (window), 
                                gtk_ui_manager_get_accel_group (menu_manager));
 
    /* Show the window and run the main loop, we're done! */
    gtk_widget_show_all (window);
    
    gtk_main ();
    
    return 0;
}
