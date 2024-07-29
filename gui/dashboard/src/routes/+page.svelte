<script>
  let count = 0;
</script>

<h1>Welcome to SvelteKit</h1>
<p>Visit <a href="https://kit.svelte.dev">kit.svelte.dev</a> to read the documentation</p>

<button on:click={() => ++count} class="p-2 bg-blue-400">{count}</button>

<a href="/test" class="p-2 bg-blue-400">Test</a>
