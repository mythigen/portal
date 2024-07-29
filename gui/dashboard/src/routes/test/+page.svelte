<script>
  let count = 0;

  $: setTimeout(() => ++count, 2000);
</script>

teehee: {count}

<a href="/" class="p-2 bg-blue-400">Return Home</a>
