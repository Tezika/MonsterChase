gameObject = 
{
    name = "BadGuy",
    initial_position = {x=1,y=1},
    physics_settings = {
        mass = 1,
        force = {x=300, y=0},
        dragness = 0.005,
        AABB = 
        {
            center = {x=0.5, y=0.5},
            extends = {x=64, y=64}
        }
    },
    render_settings = {
        sprite_name = "Data\\Badguy.dds"
    }
}