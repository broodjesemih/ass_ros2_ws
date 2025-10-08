# Legacy Scripts

Deze directory bevat de oude setup scripts die zijn vervangen door het nieuwe `complete_setup.sh` script.

## Oude Scripts (niet meer nodig)

- `setup_postgresql.sh` - PostgreSQL setup (nu onderdeel van complete_setup.sh)
- `debug_postgres.sh` - Database debugging (vervangen door test_database.sh) 
- `fix_postgres_connection.sh` - Connectie fix script (geïntegreerd)
- `start_system.sh` - Systeem starter (vervangen door run_system.sh)

## Nieuwe Workflow

In plaats van deze 4-5 verschillende scripts te gebruiken:

```bash
# ❌ Oude manier
./setup_postgresql.sh
./debug_postgres.sh  
./fix_postgres_connection.sh
./start_system.sh
```

Gebruik nu gewoon:

```bash
#   Nieuwe manier  
./complete_setup.sh   # Doet alles in één keer
./run_system.sh       # Start het systeem
```

De oude scripts worden bewaard voor referentie, maar het wordt aangeraden om het nieuwe `complete_setup.sh` script te gebruiken.
